#include "cc3200.h"
#include "uart.h"

uint8_t u8TxData[32];
char i;

void Message(void)
{
	if((Uart_GetStatus(M0P_UART0, UartFE))||(Uart_GetStatus(M0P_UART0, UartPE)))  //错误请求
	{
		Uart_ClrStatus(M0P_UART0, UartFE);            //清除帧错误标记
		Uart_ClrStatus(M0P_UART0, UartPE);            //清除奇偶校验错误标记
	}
	if(Uart_GetStatus(M0P_UART0,UartRC))              //接收到数据
	{
		Uart_ClrStatus(M0P_UART0,UartRC);
		u8TxData[0] = Uart_ReceiveData(M0P_UART0);    //接收数据
		for(i=0;i<32;i++)
		{
			Uart_SendDataPoll(M0P_UART0,u8TxData[i]); //查询方式发送数据
		}
	}
}

