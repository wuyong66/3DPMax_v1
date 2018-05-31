//Download by http://www.NewXing.com
#if !defined(MSERVERH)
#define MSERVERH

#ifdef __cplusplus
extern "C" 
{
#endif
	/*1.对单个PLC操作*/
    /*读一个或多个模拟量  参数：站号，开始地址， 读的数量， 返回数据变量指针  返回：－1表示CRC校验失败，－2表示无应答， 大于零表示接收数据成功*/
	char MODBUS_S_ReadMultiRegD(unsigned char rtu, unsigned short int RegAdd, unsigned short int RegCount, short int *list);	
	/*读一个或多个开关量  参数：站号，开始地址， 读的数量， 返回数据变量指针  返回：－1表示CRC校验失败，－2表示无应答， 大于零表示接收数据成功*/
	char MODBUS_S_ReadMultiRegM(unsigned char rtu, unsigned short int RegAdd, unsigned short int RegCount, bool *list);
	/*读一个或多个开关量  参数：站号，开始地址， 读的数量， 返回数据变量指针  返回：－1表示CRC校验失败，－2表示无应答， 大于零表示接收数据成功*/
	char MODBUS_S_ReadMultiRegM_1x(unsigned char rtu, unsigned short int RegAdd, unsigned short int RegCount, bool *list);
	/*写一个模拟量 参数：站号，写地址， 返回数据变量指针  返回：小于零失败，大于零表示成功*/
	char MODBUS_S_WriteSingRegD(unsigned char rtu, unsigned short int RegAdd, short int var);
	/*写一个模拟量 参数：站号，写地址， 返回数据变量指针  返回：小于零失败，大于零表示成功*/
	char MODBUS_S_WriteSingRegM(unsigned char rtu, unsigned short int RegAdd, bool var);
	/*写一个float型的浮点数 参数：站号，写地址，要发送的单精度浮点数 返回：小于零失败，大于零成功*/
	char MODBUS_S_WriteSingFloat(unsigned char rtu, unsigned short int RegAdd, float floatNum);

	/*2.对全部PLC操作*/
	char MODBUS_S_A_WriteSingRegD(unsigned short int RegAdd, bool var);
	char MODBUS_S_A_WriteSingRegM(unsigned short int RegAdd, short int var);

	
	/*3.端口操作*/
	char MODBUS_S_Init(unsigned long xPort, unsigned long xBabd, unsigned char xDataSize, 
				unsigned char xParity, unsigned char xStopBit);
	char MODBUS_S_UnInit();

	/*数据转换操作*/
	char FloatToByte(float floatNum,unsigned char *byteArry);

#ifdef __cplusplus
}
#endif


#endif
