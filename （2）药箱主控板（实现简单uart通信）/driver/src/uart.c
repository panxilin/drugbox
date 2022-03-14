/*************************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.    
*
* This software is owned and published by: 
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND 
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC 
* components. This software is licensed by HDSC to be adapted only 
* for use in systems utilizing HDSC components. HDSC shall not be 
* responsible for misuse or illegal use of this software for devices not 
* supported herein. HDSC is providing this software "AS IS" and will 
* not be responsible for issues arising from incorrect user implementation 
* of the software.  
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS), 
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING, 
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED 
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED 
* WARRANTY OF NONINFRINGEMENT.  
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT, 
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT 
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, 
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR 
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA, 
* SAVINGS OR PROFITS, 
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED 
* FROM, THE SOFTWARE.  
*
* This software may be replicated in part or whole for the licensed use, 
* with the restriction that this Disclaimer and Copyright notice must be 
* included with each copy of this software, whether used in part or whole, 
* at all times.                        
*/
/******************************************************************************/
/** \file uart.c
 **
 ** UART function driver API.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2017-05-17  1.0  CJ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "uart.h"
#include "gpio.h"

/**
 ******************************************************************************
 ** \addtogroup UartGroup
 ******************************************************************************/
//@{
/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable definitions ('static')                                       */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief  UART通信中断使能函数设置
 **
 ** \param [in] UARTx通道号，enIrqSel发送or接收中断使能
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_EnableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enIrqSel, TRUE);
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通信中断禁止函数设置
 **
 ** \param [in] UARTx通道号，enIrqSel发送or接收中断禁止
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_DisableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enIrqSel, FALSE);
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通道多主机模式配置
 **
 ** \param [in] UARTx通道号，stcMultiCfg多主机模式结构
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetMultiMode(M0P_UART_TypeDef* UARTx, stc_uart_multimode_t* pstcMultiCfg)
{
    if(NULL != pstcMultiCfg)
    {
        UARTx->SCON_f.ADRDET = TRUE;   
        UARTx->SADDR = pstcMultiCfg->u8SlaveAddr;
        UARTx->SADEN = pstcMultiCfg->u8SaddEn;
    }
    else
    {
        return ErrorInvalidParameter;
    }
    return Ok;
}



/**
 ******************************************************************************
 ** \brief  UART通道多机模式发送数据/地址帧配置TB8
 **
 ** \param [in] UARTx 通道号
 ** \param [in] TRUE-TB8为地址帧标志；FALSE-TB8为数据帧标志；
 **
 ** \retval Null
 ******************************************************************************/
void Uart_SetTb8(M0P_UART_TypeDef* UARTx, boolean_t bTB8Value)
{
    UARTx->SCON_f.B8CONT = bTB8Value;
}

/**
 ******************************************************************************
 ** \brief 获取RB8数值
 **
 ** \param [in] UARTx通道号
 **
 ** \retval RB8
 ******************************************************************************/
boolean_t Uart_GetRb8(M0P_UART_TypeDef* UARTx)
{
    return (UARTx->SBUF_f.DATA8);
}
/**
 ******************************************************************************
 ** \brief  UART通道多主机模式从机地址配置函数
 **
 ** \param [in] UARTx通道号，addr地址
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetSaddr(M0P_UART_TypeDef* UARTx,uint8_t u8Addr)
{
    UARTx->SADDR = u8Addr;
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通道发送或接收等功能使能设置
 **
 ** \param [in] UARTx通道号，enFunc功能
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_EnableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc)
{    
    SetBit((uint32_t)(&(UARTx->SCON)), enFunc, TRUE);
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道发送或接收等功能禁止设置
 **
 ** \param [in] UARTx通道号，enFunc功能
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_DisableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc)
{
    SetBit((uint32_t)(&(UARTx->SCON)), enFunc, FALSE);
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道通信状态获取
 **
 ** \param [in] UARTx通道号
 **
 ** \retval 状态值
 ******************************************************************************/
uint8_t Uart_GetIsr(M0P_UART_TypeDef* UARTx)
{
    return (UARTx->ISR);
}
/**
 ******************************************************************************
 ** \brief  UART通道通信状态获取
 **
 ** \param [in] UARTx通道号，enStatus获取哪个状态
 **
 ** \retval 状态值
 ******************************************************************************/
boolean_t Uart_GetStatus(M0P_UART_TypeDef* UARTx, en_uart_status_t enStatus)
{
    boolean_t bStatus = FALSE;
    ASSERT(IS_VALID_STATUS(enStatus));
    bStatus =  GetBit((uint32_t)(&(UARTx->ISR)), enStatus);
    return bStatus;
}
/**
 ******************************************************************************
 ** \brief  UART通道通信状态清除
 **
 ** \param [in] UARTx通道号
 **
 ** \retval OK
 ** \retval ErrorInvalidParameter清除失败
 ******************************************************************************/
en_result_t Uart_ClrIsr(M0P_UART_TypeDef* UARTx)
{
    UARTx->ICR = 0u;
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道通信状态清除
 **
 ** \param [in] UARTx通道号，enStatus清除哪个状态
 **
 ** \retval OK
 ** \retval ErrorInvalidParameter清除失败
 ******************************************************************************/
en_result_t Uart_ClrStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus)
{
    ASSERT(IS_VALID_STATUS(enStatus));
    SetBit((uint32_t)(&(UARTx->ICR)), enStatus, FALSE);
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道发送数据函数,查询方式调用此函数，中断方式发送不适用
 **
 ** \param [in] UARTx通道号，Data发送数据
 **
 ** \retval Ok发送成功
 ** \retval ErrorInvalidParameter发送失败
 ******************************************************************************/
en_result_t Uart_SendDataPoll(M0P_UART_TypeDef* UARTx, uint8_t u8Data)
{
    while(FALSE == Uart_GetStatus(UARTx,UartTxe))
    {}
    UARTx->SBUF_f.DATA = u8Data;
    while(FALSE == Uart_GetStatus(UARTx,UartTC))
    {}
    Uart_ClrStatus(UARTx,UartTC);       
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通道发送数据函数,中断方式调用此函数
 **
 ** \param [in] UARTx通道号，Data发送数据
 **
 ** \retval Ok发送成功
 ** \retval ErrorInvalidParameter发送失败
 ******************************************************************************/
en_result_t Uart_SendDataIt(M0P_UART_TypeDef* UARTx, uint8_t u8Data)
{ 
    UARTx->SBUF_f.DATA = u8Data; 
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通道接收数据函数
 **
 ** \param [in] UARTx通道号
 **
 ** \retval 接收数据
 ******************************************************************************/
uint8_t Uart_ReceiveData(M0P_UART_TypeDef* UARTx)
{
    return (UARTx->SBUF_f.DATA);
}

/**
 ******************************************************************************
 ** \brief  UART通道初始化函数
 **
 ** \param [in] UARTx通道号，pstcCfg初始化结构体 @ref stc_uart_cfg_t
 **
 ** \retval OK配置成功
 ** \retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_Init(M0P_UART_TypeDef* UARTx, stc_uart_cfg_t* pstcCfg)
{
    en_result_t enRet = Error;
    uint32_t u32Over[2] = {0x4, 0x3};
    uint16_t u16OverShift;
    float32_t f32Scnt=0;
    if(NULL == pstcCfg)
    {
        return ErrorInvalidParameter;
    }
    UARTx->SCON = 0;
    UARTx->SCON = (uint32_t)pstcCfg->enStopBit |
                  (uint32_t)pstcCfg->enMmdorCk |
                  (uint32_t)pstcCfg->stcBaud.enClkDiv |
                  (uint32_t)pstcCfg->enRunMode;
    if((UartMskMode1 == pstcCfg->enRunMode) || (UartMskMode3 == pstcCfg->enRunMode))
    {
        u16OverShift = u32Over[pstcCfg->stcBaud.enClkDiv/UartMsk8Or16Div];
        f32Scnt = (float32_t)(pstcCfg->stcBaud.u32Pclk)/(float32_t)(pstcCfg->stcBaud.u32Baud<<u16OverShift);        
        UARTx->SCNT = (uint16_t)(float32_t)(f32Scnt + 0.5f);
        Uart_EnableFunc(UARTx,UartRenFunc);       //<使能收发
    }
    enRet = Ok;
    return enRet;
}

//串口引脚配置
void App_PortInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    
    DDL_ZERO_STRUCT(stcGpioCfg);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE); //GPIO外设模块时钟使能
    
    stcGpioCfg.enDir = GpioDirOut;
    Gpio_Init(STK_UART0_TXD_PORT,STK_UART0_TXD_PIN,&stcGpioCfg);
    Gpio_SetAfMode(STK_UART0_TXD_PORT,STK_UART0_TXD_PIN,GpioAf7); //配置PB08 为UART0 TX
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(STK_UART0_RXD_PORT,STK_UART0_RXD_PIN,&stcGpioCfg);
    Gpio_SetAfMode(STK_UART0_RXD_PORT,STK_UART0_RXD_PIN,GpioAf7);//配置PB09 为UART0 RX
}

//串口模块配置
void App_UartCfg(void)
{
    stc_uart_cfg_t  stcCfg;
    stc_uart_multimode_t stcMulti;
    stc_uart_baud_t stcBaud;

    DDL_ZERO_STRUCT(stcCfg);
    DDL_ZERO_STRUCT(stcMulti);
    DDL_ZERO_STRUCT(stcBaud);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0,TRUE);//UART0外设模块时钟使能
    
    stcCfg.enRunMode = UartMskMode3;     //模式3
    stcCfg.enStopBit = UartMsk1bit;      //1位停止位
    stcCfg.enMmdorCk = UartMskEven;      //偶校验
    stcCfg.stcBaud.u32Baud = 9600;       //波特率9600
    stcCfg.stcBaud.enClkDiv = UartMsk8Or16Div;         //通道采样分频配置
    stcCfg.stcBaud.u32Pclk = Sysctrl_GetPClkFreq();    //获得外设时钟（PCLK）频率值
    Uart_Init(M0P_UART0, &stcCfg);       //串口初始化

    Uart_ClrStatus(M0P_UART0,UartRC);    //清接收请求
    Uart_ClrStatus(M0P_UART0,UartTC);    //清发送请求
    Uart_EnableIrq(M0P_UART0,UartRxIrq); //使能串口接收中断
//    Uart_EnableIrq(M0P_UART0,UartTxIrq); //使能串口发送中断

}

//@} // UartGroup      
