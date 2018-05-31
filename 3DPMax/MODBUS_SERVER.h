//Download by http://www.NewXing.com
#if !defined(MSERVERH)
#define MSERVERH

#ifdef __cplusplus
extern "C" 
{
#endif
	/*1.�Ե���PLC����*/
    /*��һ������ģ����  ������վ�ţ���ʼ��ַ�� ���������� �������ݱ���ָ��  ���أ���1��ʾCRCУ��ʧ�ܣ���2��ʾ��Ӧ�� �������ʾ�������ݳɹ�*/
	char MODBUS_S_ReadMultiRegD(unsigned char rtu, unsigned short int RegAdd, unsigned short int RegCount, short int *list);	
	/*��һ������������  ������վ�ţ���ʼ��ַ�� ���������� �������ݱ���ָ��  ���أ���1��ʾCRCУ��ʧ�ܣ���2��ʾ��Ӧ�� �������ʾ�������ݳɹ�*/
	char MODBUS_S_ReadMultiRegM(unsigned char rtu, unsigned short int RegAdd, unsigned short int RegCount, bool *list);
	/*��һ������������  ������վ�ţ���ʼ��ַ�� ���������� �������ݱ���ָ��  ���أ���1��ʾCRCУ��ʧ�ܣ���2��ʾ��Ӧ�� �������ʾ�������ݳɹ�*/
	char MODBUS_S_ReadMultiRegM_1x(unsigned char rtu, unsigned short int RegAdd, unsigned short int RegCount, bool *list);
	/*дһ��ģ���� ������վ�ţ�д��ַ�� �������ݱ���ָ��  ���أ�С����ʧ�ܣ��������ʾ�ɹ�*/
	char MODBUS_S_WriteSingRegD(unsigned char rtu, unsigned short int RegAdd, short int var);
	/*дһ��ģ���� ������վ�ţ�д��ַ�� �������ݱ���ָ��  ���أ�С����ʧ�ܣ��������ʾ�ɹ�*/
	char MODBUS_S_WriteSingRegM(unsigned char rtu, unsigned short int RegAdd, bool var);
	/*дһ��float�͵ĸ����� ������վ�ţ�д��ַ��Ҫ���͵ĵ����ȸ����� ���أ�С����ʧ�ܣ�������ɹ�*/
	char MODBUS_S_WriteSingFloat(unsigned char rtu, unsigned short int RegAdd, float floatNum);

	/*2.��ȫ��PLC����*/
	char MODBUS_S_A_WriteSingRegD(unsigned short int RegAdd, bool var);
	char MODBUS_S_A_WriteSingRegM(unsigned short int RegAdd, short int var);

	
	/*3.�˿ڲ���*/
	char MODBUS_S_Init(unsigned long xPort, unsigned long xBabd, unsigned char xDataSize, 
				unsigned char xParity, unsigned char xStopBit);
	char MODBUS_S_UnInit();

	/*����ת������*/
	char FloatToByte(float floatNum,unsigned char *byteArry);

#ifdef __cplusplus
}
#endif


#endif
