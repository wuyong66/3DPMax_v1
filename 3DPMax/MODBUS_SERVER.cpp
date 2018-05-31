#include "stdafx.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "MODBUS_SHARE.h"
#include "MODBUS_SERVER.h"
#include "PORT.h"
//Download by http://www.NewXing.com



unsigned char buff[256];


////////////////////////////////////////////////////////////////////////////////////////////////////
/*1.对单个PLC操作*/
/*读一个或多个模拟量  参数：站号，开始地址， 读的数量， 返回数据变量指针  返回：－1表示CRC校验失败，－2表示无应答， 大于零表示接收数据成功*/
/*40000*/

char MODBUS_S_ReadMultiRegD(unsigned char rtu, unsigned short int RegAdd, unsigned short int RegCount, short int *list)
{
	unsigned short int crc16; //无符号短整型
	unsigned short int crctmp;
	short int vartmp;
	
	memset(buff, 0x00, 255);   //buff 无符号字符型unsigned char变量 理解为8位寄存器
	buff[0]= rtu;         //站号

	buff[1]= 0x03;        //读单个寄存器功能码

	buff[2]= (unsigned char)((RegAdd-40000) >> 8);   //寄存器地址 ，循环右移，地址高八位
	buff[3]= (unsigned char)(RegAdd-40000);          //寄存器地址 ， 强制转换，取低八位

	buff[4]= (unsigned char)(RegCount >> 8);         //与寄存器地址同理
	buff[5]= (unsigned char)RegCount;
	crc16= CalcCrcFast(buff, 6);                     //CRC校验，检验前六个
	buff[6]= (unsigned char)(crc16 >> 8);            //与寄存器地址同理
	buff[7]= (unsigned char)crc16;
	
	//发送数据
	unsigned long strlen;
	if(IsOpen())   //串口是否打开？
	{
		//发送数据
		strlen= WriteChar(8, (char *)buff);  //关于普通串口的读写函数 把八个八位二进制读寄存器命令发送出去

		if(strlen==8)
		{
			//读数据
			memset(buff, 0x00, 255);   //无符号字符型初始化
			Sleep(50);
			strlen= ReadChar(255, (char *)buff, 1000);  //最大255个 超时等待1000
			if(strlen==0)
			{
				//无返回
				return(-2);				
			}
			else
			{
				
				//返回长度有效,从站号有效，读功能码有效，则解析接收缓冲区
				if(strlen== (3+(RegCount *2)+ 2) && buff[0]== rtu && buff[1]== 0x03)
				{
					crc16= CalcCrcFast(buff, 3+(RegCount*2)); //计算CRC校验码
					crctmp= buff[strlen-2];   //截取CRC校验码
					crctmp= crctmp << 8 | buff[strlen-1];  //转换为16位无符号短整型

					if(crc16== crctmp )
					{
						for(int i=0; i< RegCount; i++)
						{
							vartmp= buff[3+(2*i)];
							vartmp= vartmp << 8;
							vartmp= vartmp | buff[3+((2*i)+1)];
							
							list[i]= vartmp;    //解析数据
						}								
					}
					else
					{
						return(-1); //CRC校验失败
					}
				}
				else
				{
					return(-1); //数据返回包有误，不应该是-1
				}
			}
		}
		else
		{			
			return(-2);  //数据长度有问题
		}		
	}
	else
	{
		return(-3);  //串口还未打开
	}
	
	return(1);
}

/*读一个或多个开关量  参数：站号，开始地址， 读的数量， 返回数据变量指针  返回：－1表示CRC校验失败，－2表示无应答， 大于零表示接收数据成功*/
/*00000*/
char MODBUS_S_ReadMultiRegM(unsigned char rtu, unsigned short int RegAdd, unsigned short int RegCount, bool *list)
{
	
	unsigned short int crc16;
	unsigned short int crctmp;
	
	memset(buff, 0x00, 255);
	buff[0]= rtu;
	buff[1]= 0x01;
	buff[2]= (unsigned char)(RegAdd >> 8);
	buff[3]= (unsigned char)RegAdd;
	buff[4]= (unsigned char)(RegCount >> 8);
	buff[5]= (unsigned char)RegCount;
	crc16= CalcCrcFast(buff, 6);
	buff[6]= (unsigned char)(crc16 >> 8);
	buff[7]= (unsigned char)crc16;
	
	//发送数据
	unsigned long strlen;
	if(IsOpen())
	{
		//发送数据
		strlen= WriteChar(8, (char *)buff);
		if(strlen==8)
		{
			//读数据
			memset(buff, 0x00, 255);
			Sleep(50);
			strlen= ReadChar(255, (char *)buff, 1000);
			if(strlen==0)
			{
				//无返回
				return(-2);				
			}
			else
			{
				//返回长度有效,解析接收缓冲区
				if(strlen== (3+((RegCount+7)/8)+ 2) && buff[0]== rtu && buff[1]== 0x01)
				{
					crc16= CalcCrcFast(buff, 3+((RegCount +7)/8));
					crctmp= buff[strlen-2];
					crctmp= crctmp << 8 | buff[strlen-1];
					if(crc16== crctmp )
					{
						unsigned char row=0, col=0;						
						for(int i=0; i<RegCount; i++)
						{						
							row= i / 8;							
							col= i % 8;							
							list[i]= buff[3 + row] >> col & 0x01;
						}								
					}
					else
					{
						return(-1);
					}
				}
				else
				{
					return(-1);
				}
			}
		}
		else
		{			
			return(-2);
		}		
	}
	else
	{
		return(-2);
	}
	
	return(1);
}

/*读一个或多个开关量  参数：站号，开始地址， 读的数量， 返回数据变量指针  返回：－1表示CRC校验失败，－2表示无应答， 大于零表示接收数据成功*/
/*10000*/
char MODBUS_S_ReadMultiRegM_1x(unsigned char rtu, unsigned short int RegAdd, unsigned short int RegCount, bool *list)
{
	unsigned short int crc16;
	unsigned short int crctmp;
	
	memset(buff, 0x00, 255);
	buff[0]= rtu;
	buff[1]= 0x02;
	buff[2]= (unsigned char)((RegAdd-10000)>> 8);
	buff[3]= (unsigned char)(RegAdd-10000);
	buff[4]= (unsigned char)(RegCount >> 8);
	buff[5]= (unsigned char)RegCount;
	crc16= CalcCrcFast(buff, 6);
	buff[6]= (unsigned char)(crc16 >> 8);
	buff[7]= (unsigned char)crc16;
	
	//发送数据
	unsigned long strlen;
	if(IsOpen())
	{
		//发送数据
		strlen= WriteChar(8, (char *)buff);
		if(strlen==8)
		{
			//读数据
			memset(buff, 0x00, 255);
			Sleep(50);
			strlen= ReadChar(255, (char *)buff, 1000);
			if(strlen==0)
			{
				//无返回
				return(-2);				
			}
			else
			{
				//返回长度有效,解析接收缓冲区
				if(strlen == (3+((RegCount+7)/8)+ 2) && buff[0]== rtu && buff[1]== 0x02)
				{
					crc16= CalcCrcFast(buff, 3+((RegCount +7)/8));
					crctmp= buff[strlen-2];
					crctmp= crctmp << 8 | buff[strlen-1];
					if(crc16== crctmp )
					{
						unsigned char row=0, col=0;						
						for(int i=0; i<RegCount; i++)
						{						
							row= i / 8;							
							col= i % 8;							
							list[i]= buff[3 + row] >> col & 0x01;
						}								
					}
					else
					{
						return(-1);
					}
				}
				else
				{
					return(-1);
				}
			}
		}
		else
		{			
			return(-2);
		}		
	}
	else
	{
		return(-2);
	}
	
	return(1);
}

/*写一个模拟量（保持寄存器） 参数：站号，写地址， 返回数据变量指针  返回：小于零失败，大于零表示成功*/
/*40000*/  
char MODBUS_S_WriteSingRegD(unsigned char rtu, unsigned short int RegAdd, short int var)
{
	unsigned short int crc16;
	
	memset(buff, 0x00, 255);
	buff[0]= rtu;
	buff[1]= 0x06;
	buff[2]= (unsigned char)((RegAdd-40000) >> 8);
	buff[3]= (unsigned char)(RegAdd-40000);
	//数据
	buff[4]= (unsigned char)(var >> 8);
	buff[5]= (unsigned char)var;

	crc16= CalcCrcFast(buff, 6);
	buff[6]= (unsigned char)(crc16 >> 8);
	buff[7]= (unsigned char)crc16;

	//发送数据
	unsigned long strlen;
	if(IsOpen())
	{
		//发送数据
		strlen= WriteChar(8, (char *)buff);
		if(strlen==8)
		{
			Sleep(50);
			strlen= ReadChar(255, (char *)buff, 1000);
			//返回长度有效,解析接收缓冲区
			if(!(strlen== 8 && buff[0]== rtu && buff[1]== 0x06))
			{
				return(-1);
			}
		}
		else
		{			
			return(-1);
		}		
	}
	else
	{
		return(-1);
	}
	
	return(1);		
}


/*写一个模拟量 参数：站号，写地址， 返回数据变量指针  返回：小于零失败，大于零表示成功*/
char MODBUS_S_WriteSingRegM(unsigned char rtu, unsigned short int RegAdd, bool var)
{
	unsigned short int crc16;
	
	memset(buff, 0x00, 255);
	buff[0]= rtu;
	buff[1]= 0x05;
	buff[2]= (unsigned char)(RegAdd >> 8);
	buff[3]= (unsigned char)RegAdd;
	if(var)
	{
		buff[4]= 0xff;
		buff[5]= 0x00;
	}
	else
	{
		buff[4]= 0x00;
		buff[5]= 0x00;
	}
	crc16= CalcCrcFast(buff, 6);
	buff[6]= (unsigned char)(crc16 >> 8);
	buff[7]= (unsigned char)crc16;
	
	//发送数据
	unsigned long strlen;
	if(IsOpen())
	{
		//发送数据
		Sleep(50);
		strlen= WriteChar(8, (char *)buff);
		if(strlen==8)
		{
			Sleep(50);
			strlen= ReadChar(255, (char *)buff, 1000);
			//返回长度有效,解析接收缓冲区
			if(!(strlen== 8 && buff[0]== rtu && buff[1]== 0x05))
			{
				return(-1);
			}
		}
		else
		{			
			return(-1);
		}		
	}
	else
	{
		return(-1);
	}
	
	return(1);	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*2.对全部PLC操作*/
char MODBUS_S_A_WriteSingRegD(unsigned short int RegAdd, short int var)
{
	unsigned short int crc16;
	
	memset(buff, 0x00, 255);
	buff[0]= 0xff;
	buff[1]= 0x06;
	buff[2]= (unsigned char)((RegAdd -40000) >> 8);
	buff[3]= (unsigned char)(RegAdd -40000);
	buff[4]= (unsigned char)(var >> 8);
	buff[5]= (unsigned char)var;
	crc16= CalcCrcFast(buff, 6);
	buff[6]= (unsigned char)(crc16 >> 8);
	buff[7]= (unsigned char)crc16;

	//发送数据
	unsigned long strlen;
	if(IsOpen())
	{
		//发送数据
		strlen= WriteChar(8, (char *)buff);
		if(strlen!=8)
		{			
			return(-1);
		}		
	}
	else
	{
		return(-1);
	}
	
	return(1);	
}

char MODBUS_S_A_WriteSingRegM(unsigned short int RegAdd, bool var)
{
	unsigned short int crc16;
	
	memset(buff, 0x00, 255);
	buff[0]= 0xff;
	buff[1]= 0x05;
	buff[2]= (unsigned char)(RegAdd >> 8);
	buff[3]= (unsigned char)RegAdd;
	if(var)
	{
		buff[4]= 0xff;
		buff[5]= 0x00;
	}
	else
	{
		buff[4]= 0x00;
		buff[5]= 0x00;
	}
	crc16= CalcCrcFast(buff, 6);
	buff[6]= (unsigned char)(crc16 >> 8);
	buff[7]= (unsigned char)crc16;
	
	//发送数据
	unsigned long strlen;
	if(IsOpen())
	{
		//发送数据
		strlen= WriteChar(8, (char *)buff);
		if(strlen!=8)
		{			
			return(-1);
		}		
	}
	else
	{
		return(-1);
	}
	
	return(1);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
char MODBUS_S_Init(unsigned long xPort, unsigned long xBabd, unsigned char xDataSize, 
				unsigned char xParity, unsigned char xStopBit)
{
	/*
	Parity :
	EVENPARITY Even 
	MARKPARITY Mark 
	NOPARITY No parity 
	ODDPARITY Odd 
	SPACEPARITY Space 
	*/	
	/*BaudRate:
	CBR_110
	CBR_19200
	CBR_300
	CBR_38400
	CBR_600
	CBR_56000
	CBR_1200
	CBR_57600
	CBR_2400
	CBR_115200
	CBR_4800
	CBR_128000
	CBR_9600
	CBR_256000
	CBR_14400	
	*/
	/*
	ONESTOPBIT 1 stop bit 
	ONE5STOPBITS 1.5 stop bits 
	TWOSTOPBITS 
	*/

	if(OpenPort(xPort,xBabd,xDataSize,xParity, xStopBit,4096,4096,1000))
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

char MODBUS_S_UnInit()
{
	ClosePort();
	return(1);
}
//数据转换float to byte
char FloatToByte(float floatNum,unsigned char *byteArry)
{
	char* pchar = (char*)&floatNum;
	for(int i = 0; i < sizeof(float); i++)
	{
		*byteArry = *pchar;
		pchar++;
		byteArry++;
	}
	return 1;
}

//写一个单精度浮点数 地址只能为偶数，与visual modbus slave一致
char MODBUS_S_WriteSingFloat(unsigned char rtu, unsigned short int RegAdd, float floatNum)
{
	unsigned short int crc16;
	unsigned char float2Hex[4];

	FloatToByte(floatNum,float2Hex);
	
	memset(buff, 0x00, 255);
	buff[0]= rtu;

	buff[1]= 0x06;

	buff[2]= (unsigned char)((RegAdd-40000) >> 8);
	buff[3]= (unsigned char)(RegAdd-40000);

	buff[4] = float2Hex[1];
	buff[5] = float2Hex[0];

	crc16= CalcCrcFast(buff, 6);
	buff[6]= (unsigned char)(crc16 >> 8);
	buff[7]= (unsigned char)crc16;

	//发送数据
	unsigned long strlen_1;
	if(IsOpen())
	{
		//发送数据
		strlen_1= WriteChar(8, (char *)buff);
		if(strlen_1==8)
		{
			Sleep(50);
			strlen_1= ReadChar(255, (char *)buff, 1000);
			//返回长度有效,解析接收缓冲区
			if(!(strlen_1== 8 && buff[0]== rtu && buff[1]== 0x06))
			{
				return(-1);
			}
		}
		else
		{			
			return(-1);
		}		
	}
	else
	{
		return(-1);
	}

	memset(buff, 0x00, 255);
	buff[0]= rtu;
	buff[1]= 0x06;
	buff[2]= (unsigned char)(((RegAdd+1)-40000) >> 8);
	buff[3]= (unsigned char)((RegAdd+1)-40000);

	buff[4] = float2Hex[3];
	buff[5] = float2Hex[2];
	crc16= CalcCrcFast(buff, 6);
	buff[6]= (unsigned char)(crc16 >> 8);
	buff[7]= (unsigned char)crc16;

	//发送数据
	unsigned long strlen_2;
	if(IsOpen())
	{
		//发送数据
		strlen_2= WriteChar(8, (char *)buff);
		if(strlen_2==8)
		{
			Sleep(50);
			strlen_2= ReadChar(255, (char *)buff, 1000);
			//返回长度有效,解析接收缓冲区
			if(!(strlen_2== 8 && buff[0]== rtu && buff[1]== 0x06))
			{
				return(-1);
			}
		}
		else
		{			
			return(-1);
		}		
	}
	else
	{
		return(-1);
	}
	
	return(1);		
}




