#include "cc3200.h"
#include "uart.h"

uint8_t u8TxData[32];
char i;

void Message(void)
{
	if((Uart_GetStatus(M0P_UART0, UartFE))||(Uart_GetStatus(M0P_UART0, UartPE)))  //��������
	{
		Uart_ClrStatus(M0P_UART0, UartFE);            //���֡������
		Uart_ClrStatus(M0P_UART0, UartPE);            //�����żУ�������
	}
	if(Uart_GetStatus(M0P_UART0,UartRC))              //���յ�����
	{
		Uart_ClrStatus(M0P_UART0,UartRC);
		u8TxData[0] = Uart_ReceiveData(M0P_UART0);    //��������
		for(i=0;i<32;i++)
		{
			Uart_SendDataPoll(M0P_UART0,u8TxData[i]); //��ѯ��ʽ��������
		}
	}
}

