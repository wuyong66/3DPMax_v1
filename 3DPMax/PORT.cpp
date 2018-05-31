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
//ͨѶ�˿��Ƿ��
inline bool IsOpen()
{
	return hCom != INVALID_HANDLE_VALUE;
} 

//���ó�ʱ
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

//����DCB����
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
			printf ("����: %d << �ȵ�ͨѶ�ڲ���ʧ��.\n", GetLastError());
		#endif
		
		ClosePort();
		return (false);
	}   
	//����ͨѶ����   	
	dcb.DCBlength= sizeof(DCB);	
	dcb.BaudRate = xBabd;     // set the baud rate
	dcb.ByteSize = xDataSize; // data size, xmit, and rcv
	dcb.Parity =   xParity;   // no parity bit
	dcb.StopBits = xStopBit;  // one stop bit	
	if (!SetCommState(hCom, &dcb)) 
	{
		#ifdef _DEBUG
			printf ("����: %d << ����ͨѶ�˿ڲ���ʧ��.\n", GetLastError());
		#endif
		ClosePort();
		return (false);
	}   

	return true;
}

//���ö˿ڻ�������С
bool SetPortBuffSize(unsigned long InputBuffSize, unsigned long OutputBuffSize)
{
	if(!IsOpen())  
	{
		return false;   
	} 
	
	if(!SetupComm(hCom, InputBuffSize, OutputBuffSize))
	{
		#ifdef _DEBUG
			printf ("����: %d << ����ͨѶ�˿ڻ���ʧ��.\n", GetLastError());
		#endif
		ClosePort();
		return (false);
	}   

	return true;
}

//�������л�����
void ClearBuffer()
{
	if(!IsOpen())  
	{
		return;   
	}

	PurgeComm(hCom, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
}

//��ǰ���ջ������ֽ���Ŀ; 
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

//��ǰ���ͻ������ֽ���Ŀ; 
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

///�򿪴���//////////////////////////////////////////////////////////////////////////////////////////////////////////// 
bool OpenPort(unsigned long xPort, unsigned long xBabd, unsigned char xDataSize, 
				unsigned char xParity, unsigned char xStopBit, unsigned long InputBuffSize,
				unsigned long OutputBuffSize, unsigned long dwTimerOut)
{   
	if(IsOpen())
	{
		ClosePort();
	}
	
	//�����¼�    
	memset(&m_overlappedRead,0,sizeof(OVERLAPPED));
	m_overlappedRead.hEvent= CreateEvent(NULL,FALSE,TRUE,"portread");
	ASSERT(m_overlappedRead.hEvent != INVALID_HANDLE_VALUE);

	memset(&m_overlappedWrite,0,sizeof(OVERLAPPED));   
	m_overlappedWrite.hEvent= CreateEvent(NULL,FALSE,TRUE,"portwrite");  
	ASSERT(m_overlappedWrite.hEvent != INVALID_HANDLE_VALUE);
	//ȡ�ô����ַ�
	char com_str[255];
	strcpy(com_str, "COM");
	ltoa(xPort, com_str + 3, 10);
	//��ͨѶ�˿� 
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
			printf ("����: %d << ��ͨѶ��ʧ��,�����Ƿ��Ѿ���װ�����豸.\n", GetLastError());
		#endif
		return (false);
	}     
	SetPortBuffSize(InputBuffSize,OutputBuffSize);
	SetDCBParm(xBabd,xDataSize,xParity,xStopBit);	
	SetTimerOut(dwTimerOut);	
	//��������
	PurgeComm(hCom, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	//�����ɹ�
	#ifdef _DEBUG
		printf ("�ɹ������˿� %d.\n", com_str);
	#endif
	return(true);
}


//�رմ���;
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


//�첽������
unsigned long ReadChar(unsigned long dwBufferLength, char *buff, unsigned long dwWaitTime=20)
{   
	if(!IsOpen())  
	{
		return(0);   
	}
	
	DWORD		dwError;
	COMSTAT		Stat;  
	if(::ClearCommError(hCom, &dwError, &Stat) && dwError > 0)	//�������
	{
		::PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR); /*������뻺����*/
		return 0;
	}
	if(!Stat.cbInQue)// ������������
	{
		return 0;
	}

	unsigned long uReadLength = 0;
	dwBufferLength = dwBufferLength - 1 > Stat.cbInQue ? Stat.cbInQue : dwBufferLength - 1;
	if(!::ReadFile(hCom, buff, dwBufferLength, &uReadLength, &m_overlappedRead)) //2000 �� ReadFile ʼ�շ��� True
	{
		if(::GetLastError() == ERROR_IO_PENDING) // �����첽I/O
		{
			WaitForSingleObject(m_overlappedRead.hEvent, dwWaitTime);	//�ȴ�20ms
			if(!::GetOverlappedResult(hCom, &m_overlappedRead, &uReadLength, false))
			{
				if(::GetLastError() != ERROR_IO_INCOMPLETE)//��������
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



//�첽д���� 
unsigned long WriteChar(unsigned long dwBufferLength, char *buff)
{
	if(!IsOpen())
	{
		return 0;
	}

	DWORD dwError;
	if(ClearCommError(hCom, &dwError, NULL) && dwError > 0)	//�������
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

