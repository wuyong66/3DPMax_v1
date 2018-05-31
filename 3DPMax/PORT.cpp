//Download by http://www.NewXing.com
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "PORT.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
DCB dcb;
COMMTIMEOUTS CommTimerOuts;
HANDLE hCom= INVALID_HANDLE_VALUE;

OVERLAPPED m_overlappedRead;
OVERLAPPED m_overlappedWrite;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//通讯端口是否打开
inline bool IsOpen()
{
	return hCom != INVALID_HANDLE_VALUE;
} 

//设置超时
void SetTimerOut(unsigned long dwTimerOut= 5000)
{
	if(!IsOpen())  
	{
		return;   
	}
	
	CommTimerOuts.ReadIntervalTimeout= MAXDWORD;
	CommTimerOuts.ReadTotalTimeoutConstant= 0;
	CommTimerOuts.ReadTotalTimeoutMultiplier= 0;
	CommTimerOuts.WriteTotalTimeoutConstant= dwTimerOut;
	CommTimerOuts.WriteTotalTimeoutMultiplier= 0;

	SetCommTimeouts(hCom, &CommTimerOuts);
}

//设置DCB参数
bool SetDCBParm(unsigned long xBabd, unsigned char xDataSize, 
				unsigned char xParity, unsigned char xStopBit)
{
	if(!IsOpen())  
	{
		return false;   
	}
	
	if (!GetCommState(hCom, &dcb)) 
	{
		#ifdef _DEBUG
			printf ("错误: %d << 等到通讯口参数失败.\n", GetLastError());
		#endif
		
		ClosePort();
		return (false);
	}   
	//设置通讯参数   	
	dcb.DCBlength= sizeof(DCB);	
	dcb.BaudRate = xBabd;     // set the baud rate
	dcb.ByteSize = xDataSize; // data size, xmit, and rcv
	dcb.Parity =   xParity;   // no parity bit
	dcb.StopBits = xStopBit;  // one stop bit	
	if (!SetCommState(hCom, &dcb)) 
	{
		#ifdef _DEBUG
			printf ("错误: %d << 设置通讯端口参数失败.\n", GetLastError());
		#endif
		ClosePort();
		return (false);
	}   

	return true;
}

//设置端口缓冲区大小
bool SetPortBuffSize(unsigned long InputBuffSize, unsigned long OutputBuffSize)
{
	if(!IsOpen())  
	{
		return false;   
	} 
	
	if(!SetupComm(hCom, InputBuffSize, OutputBuffSize))
	{
		#ifdef _DEBUG
			printf ("错误: %d << 设置通讯端口缓冲失败.\n", GetLastError());
		#endif
		ClosePort();
		return (false);
	}   

	return true;
}

//清理所有缓冲区
void ClearBuffer()
{
	if(!IsOpen())  
	{
		return;   
	}

	PurgeComm(hCom, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
}

//当前接收缓冲区字节数目; 
unsigned long GetInBuffCount()
{
	if(!IsOpen())  
	{
	return(0);   
	}

	DWORD     dwErrorFalgs;
	COMSTAT   Comstat;

	ClearCommError(hCom, &dwErrorFalgs, &Comstat);
	return Comstat.cbInQue;
}

//当前发送缓冲区字节数目; 
unsigned long GetOutBuffCount()
{
	if(!IsOpen())  
	{
		return false;   
	}

	DWORD     dwErrorFalgs;
	COMSTAT   Comstat;

	ClearCommError(hCom, &dwErrorFalgs, &Comstat);
	return Comstat.cbOutQue;
}

///打开串口//////////////////////////////////////////////////////////////////////////////////////////////////////////// 
bool OpenPort(unsigned long xPort, unsigned long xBabd, unsigned char xDataSize, 
				unsigned char xParity, unsigned char xStopBit, unsigned long InputBuffSize,
				unsigned long OutputBuffSize, unsigned long dwTimerOut)
{   
	if(IsOpen())
	{
		ClosePort();
	}
	
	//设置事件    
	memset(&m_overlappedRead,0,sizeof(OVERLAPPED));
	m_overlappedRead.hEvent= CreateEvent(NULL,FALSE,TRUE,"portread");
	ASSERT(m_overlappedRead.hEvent != INVALID_HANDLE_VALUE);

	memset(&m_overlappedWrite,0,sizeof(OVERLAPPED));   
	m_overlappedWrite.hEvent= CreateEvent(NULL,FALSE,TRUE,"portwrite");  
	ASSERT(m_overlappedWrite.hEvent != INVALID_HANDLE_VALUE);
	//取得串口字符
	char com_str[255];
	strcpy(com_str, "COM");
	ltoa(xPort, com_str + 3, 10);
	//打开通讯端口 
	hCom = CreateFile(com_str,
					GENERIC_READ | GENERIC_WRITE,
					0,    
					NULL, 
					OPEN_EXISTING, 
					FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,    
					NULL  
					);
	if (hCom == INVALID_HANDLE_VALUE) 
	{
		#ifdef _DEBUG
			printf ("错误: %d << 打开通讯口失败,请检查是否已经安装串口设备.\n", GetLastError());
		#endif
		return (false);
	}     
	SetPortBuffSize(InputBuffSize,OutputBuffSize);
	SetDCBParm(xBabd,xDataSize,xParity,xStopBit);	
	SetTimerOut(dwTimerOut);	
	//清理缓冲器
	PurgeComm(hCom, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	//启动成功
	#ifdef _DEBUG
		printf ("成功开启端口 %d.\n", com_str);
	#endif
	return(true);
}


//关闭串口;
void ClosePort()
{
	if(IsOpen())
	{
		CloseHandle(hCom);		
		hCom= INVALID_HANDLE_VALUE;
	}    
	
	//ResetEvent(m_overlappedRead.hEvent);
	//ResetEvent(m_overlappedWrite.hEvent);	

    if(m_overlappedRead.hEvent!=NULL) 
    {
        CloseHandle(m_overlappedRead.hEvent);        
    }
    if(m_overlappedWrite.hEvent!=NULL) 
    {
        CloseHandle(m_overlappedWrite.hEvent);        
    }	
}


//异步读数据
unsigned long ReadChar(unsigned long dwBufferLength, char *buff, unsigned long dwWaitTime=20)
{   
	if(!IsOpen())  
	{
		return(0);   
	}
	
	DWORD		dwError;
	COMSTAT		Stat;  
	if(::ClearCommError(hCom, &dwError, &Stat) && dwError > 0)	//清除错误
	{
		::PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR); /*清除输入缓冲区*/
		return 0;
	}
	if(!Stat.cbInQue)// 缓冲区无数据
	{
		return 0;
	}

	unsigned long uReadLength = 0;
	dwBufferLength = dwBufferLength - 1 > Stat.cbInQue ? Stat.cbInQue : dwBufferLength - 1;
	if(!::ReadFile(hCom, buff, dwBufferLength, &uReadLength, &m_overlappedRead)) //2000 下 ReadFile 始终返回 True
	{
		if(::GetLastError() == ERROR_IO_PENDING) // 结束异步I/O
		{
			WaitForSingleObject(m_overlappedRead.hEvent, dwWaitTime);	//等待20ms
			if(!::GetOverlappedResult(hCom, &m_overlappedRead, &uReadLength, false))
			{
				if(::GetLastError() != ERROR_IO_INCOMPLETE)//其他错误
				{
					uReadLength = 0;
				}
			}
		}
		else
		{
			uReadLength = 0;
		}
	}
		
	return uReadLength;
}



//异步写数据 
unsigned long WriteChar(unsigned long dwBufferLength, char *buff)
{
	if(!IsOpen())
	{
		return 0;
	}

	DWORD dwError;
	if(ClearCommError(hCom, &dwError, NULL) && dwError > 0)	//清除错误
	{
		PurgeComm(hCom, PURGE_TXABORT | PURGE_TXCLEAR);	
	}

	unsigned long uWriteLength = 0;
	if(!WriteFile(hCom, buff, dwBufferLength, &uWriteLength, &m_overlappedWrite))
	{
		if(GetLastError() == ERROR_IO_PENDING)
		{
			DWORD m_tmp=0;
			m_tmp= WaitForSingleObject(m_overlappedWrite.hEvent, 1000);
			if(m_tmp== WAIT_TIMEOUT || m_tmp== WAIT_ABANDONED)
			{
				return(0);
			}
			else if(m_tmp== WAIT_OBJECT_0)
			{			
				if(!GetOverlappedResult(hCom,&m_overlappedWrite,&uWriteLength,false))
				{
					return(0);		
				}
				else
				{
					return uWriteLength;		
				}
			}
			
			uWriteLength = 0;
		}
	}

	return uWriteLength;  
}

