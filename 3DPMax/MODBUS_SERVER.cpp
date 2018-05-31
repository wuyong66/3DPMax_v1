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
/*1.�Ե���PLC����*/
/*��һ������ģ����  ������վ�ţ���ʼ��ַ�� ���������� �������ݱ���ָ��  ���أ���1��ʾCRCУ��ʧ�ܣ���2��ʾ��Ӧ�� �������ʾ�������ݳɹ�*/
/*40000*/

char MODBUS_S_ReadMultiRegD(unsigned char rtu, unsigned short int RegAdd, unsigned short int RegCount, short int *list)
{
	unsigned short int crc16; //�޷��Ŷ�����
	unsigned short int crctmp;
	short int vartmp;
	
	memset(buff, 0x00, 255);   //buff �޷����ַ���unsigned char���� ���Ϊ8λ�Ĵ���
	buff[0]= rtu;         //վ��

	buff[1]= 0x03;        //�������Ĵ���������

	buff[2]= (unsigned char)((RegAdd-40000) >> 8);   //�Ĵ�����ַ ��ѭ�����ƣ���ַ�߰�λ
	buff[3]= (unsigned char)(RegAdd-40000);          //�Ĵ�����ַ �� ǿ��ת����ȡ�Ͱ�λ

	buff[4]= (unsigned char)(RegCount >> 8);         //��Ĵ�����ַͬ��
	buff[5]= (unsigned char)RegCount;
	crc16= CalcCrcFast(buff, 6);                     //CRCУ�飬����ǰ����
	buff[6]= (unsigned char)(crc16 >> 8);            //��Ĵ�����ַͬ��
	buff[7]= (unsigned char)crc16;
	
	//��������
	unsigned long strlen;
	if(IsOpen())   //�����Ƿ�򿪣�
	{
		//��������
		strlen= WriteChar(8, (char *)buff);  //������ͨ���ڵĶ�д���� �Ѱ˸���λ�����ƶ��Ĵ�������ͳ�ȥ

		if(strlen==8)
		{
			//������
			memset(buff, 0x00, 255);   //�޷����ַ��ͳ�ʼ��
			Sleep(50);
			strlen= ReadChar(255, (char *)buff, 1000);  //���255�� ��ʱ�ȴ�1000
			if(strlen==0)
			{
				//�޷���
				return(-2);				
			}
			else
			{
				
				//���س�����Ч,��վ����Ч������������Ч����������ջ�����
				if(strlen== (3+(RegCount *2)+ 2) && buff[0]== rtu && buff[1]== 0x03)
				{
					crc16= CalcCrcFast(buff, 3+(RegCount*2)); //����CRCУ����
					crctmp= buff[strlen-2];   //��ȡCRCУ����
					crctmp= crctmp << 8 | buff[strlen-1];  //ת��Ϊ16λ�޷��Ŷ�����

					if(crc16== crctmp )
					{
						for(int i=0; i< RegCount; i++)
						{
							vartmp= buff[3+(2*i)];
							vartmp= vartmp << 8;
							vartmp= vartmp | buff[3+((2*i)+1)];
							
							list[i]= vartmp;    //��������
						}								
					}
					else
					{
						return(-1); //CRCУ��ʧ��
					}
				}
				else
				{
					return(-1); //���ݷ��ذ����󣬲�Ӧ����-1
				}
			}
		}
		else
		{			
			return(-2);  //���ݳ���������
		}		
	}
	else
	{
		return(-3);  //���ڻ�δ��
	}
	
	return(1);
}

/*��һ������������  ������վ�ţ���ʼ��ַ�� ���������� �������ݱ���ָ��  ���أ���1��ʾCRCУ��ʧ�ܣ���2��ʾ��Ӧ�� �������ʾ�������ݳɹ�*/
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
	
	//��������
	unsigned long strlen;
	if(IsOpen())
	{
		//��������
		strlen= WriteChar(8, (char *)buff);
		if(strlen==8)
		{
			//������
			memset(buff, 0x00, 255);
			Sleep(50);
			strlen= ReadChar(255, (char *)buff, 1000);
			if(strlen==0)
			{
				//�޷���
				return(-2);				
			}
			else
			{
				//���س�����Ч,�������ջ�����
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

/*��һ������������  ������վ�ţ���ʼ��ַ�� ���������� �������ݱ���ָ��  ���أ���1��ʾCRCУ��ʧ�ܣ���2��ʾ��Ӧ�� �������ʾ�������ݳɹ�*/
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
	
	//��������
	unsigned long strlen;
	if(IsOpen())
	{
		//��������
		strlen= WriteChar(8, (char *)buff);
		if(strlen==8)
		{
			//������
			memset(buff, 0x00, 255);
			Sleep(50);
			strlen= ReadChar(255, (char *)buff, 1000);
			if(strlen==0)
			{
				//�޷���
				return(-2);				
			}
			else
			{
				//���س�����Ч,�������ջ�����
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

/*дһ��ģ���������ּĴ����� ������վ�ţ�д��ַ�� �������ݱ���ָ��  ���أ�С����ʧ�ܣ��������ʾ�ɹ�*/
/*40000*/  
char MODBUS_S_WriteSingRegD(unsigned char rtu, unsigned short int RegAdd, short int var)
{
	unsigned short int crc16;
	
	memset(buff, 0x00, 255);
	buff[0]= rtu;
	buff[1]= 0x06;
	buff[2]= (unsigned char)((RegAdd-40000) >> 8);
	buff[3]= (unsigned char)(RegAdd-40000);
	//����
	buff[4]= (unsigned char)(var >> 8);
	buff[5]= (unsigned char)var;

	crc16= CalcCrcFast(buff, 6);
	buff[6]= (unsigned char)(crc16 >> 8);
	buff[7]= (unsigned char)crc16;

	//��������
	unsigned long strlen;
	if(IsOpen())
	{
		//��������
		strlen= WriteChar(8, (char *)buff);
		if(strlen==8)
		{
			Sleep(50);
			strlen= ReadChar(255, (char *)buff, 1000);
			//���س�����Ч,�������ջ�����
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


/*дһ��ģ���� ������վ�ţ�д��ַ�� �������ݱ���ָ��  ���أ�С����ʧ�ܣ��������ʾ�ɹ�*/
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
	
	//��������
	unsigned long strlen;
	if(IsOpen())
	{
		//��������
		Sleep(50);
		strlen= WriteChar(8, (char *)buff);
		if(strlen==8)
		{
			Sleep(50);
			strlen= ReadChar(255, (char *)buff, 1000);
			//���س�����Ч,�������ջ�����
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
/*2.��ȫ��PLC����*/
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

	//��������
	unsigned long strlen;
	if(IsOpen())
	{
		//��������
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
	
	//��������
	unsigned long strlen;
	if(IsOpen())
	{
		//��������
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
//����ת��float to byte
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

//дһ�������ȸ����� ��ַֻ��Ϊż������visual modbus slaveһ��
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

	//��������
	unsigned long strlen_1;
	if(IsOpen())
	{
		//��������
		strlen_1= WriteChar(8, (char *)buff);
		if(strlen_1==8)
		{
			Sleep(50);
			strlen_1= ReadChar(255, (char *)buff, 1000);
			//���س�����Ч,�������ջ�����
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

	//��������
	unsigned long strlen_2;
	if(IsOpen())
	{
		//��������
		strlen_2= WriteChar(8, (char *)buff);
		if(strlen_2==8)
		{
			Sleep(50);
			strlen_2= ReadChar(255, (char *)buff, 1000);
			//���س�����Ч,�������ջ�����
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




