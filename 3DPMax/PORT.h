//Download by http://www.NewXing.com
#if !defined(MPORT)
#define MPORT


#ifdef __cplusplus
extern "C" 
{
#endif

	inline bool IsOpen();
	bool OpenPort(unsigned long xPort, unsigned long xBabd, unsigned char xDataSize, 
				unsigned char xParity, unsigned char xStopBit, unsigned long InputBuffSize, 
				unsigned long OutputBuffSize, unsigned long dwTimerOut);
	void ClosePort();
	void ClearBuffer();
	unsigned long ReadChar(unsigned long dwBufferLength, char *buff, unsigned long dwWaitTime);
	unsigned long WriteChar(unsigned long dwBufferLength, char *buff);
    
#ifdef __cplusplus
}
#endif

#endif
