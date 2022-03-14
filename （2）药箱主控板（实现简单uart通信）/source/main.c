/******************************************************************************
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
/** \file main.c
 **
 ** A detaiBee description is available at
 ** @link Sample Group Some description @endlink
 **
 **   - 2016-02-16  1.0  XYZ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "lcd.h"
#include "crd7601.h"
#include "cc3200.h"
#include "lpm.h"
#include "gpio.h"
#include "rtc.h"
#include "uart.h"
#include "ddl.h"

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')                            
 ******************************************************************************/
/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')                                         
 ******************************************************************************/
uint8_t StateNumber=0,ModifyNumber=0,\
		KEY1Mark=0,KEY2Mark=0,KEY3Mark=0,KEY4Mark=0;
uint16_t SecondMark=0;
/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/******************************************************************************
 * Local variable definitions ('static')                                      
 ******************************************************************************/

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')                             
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
static void App_UserKeyInit(void);
static void App_BeeInit(void);
void PortA_IRQHandler(void);
void Bee(void);

/********************************************************************************
 ** \brief  主函数
 ** 
 ** @param  无
 ** \retval 无
 **
 ******************************************************************************/ 
int32_t main(void)
{	
#if 1	//程序初始化
//	uint16_t i=0,j=0;
	Sysctrl_ClkSourceEnable(SysctrlClkRCL,TRUE);            //< 使能RCL时钟
	Sysctrl_SetRCLTrim(SysctrlRclFreq32768);                //< 配置内部低速时钟频率为32.768kHz
	Sysctrl_SetPeripheralGate(SysctrlPeripheralLcd,TRUE);   //< 开启LCD时钟
	App_LcdCfg();				//< LCD模式配置
	App_PortCfg();				//<LCD端口配置
	App_BeeInit();				//<蜂鸣器初始化
	App_RtcCfg();				//<RTC寄存器配置			
	App_ClkCfg();				//<时钟配置
	App_UserKeyInit();			//<按键初始化	
	App_PortInit();				//<UART初始化
	App_UartCfg();				//<UART配置
	Rtc_Cmd(TRUE);  			//<使能RTC时钟
    EnableNvic(PORTA_IRQn, IrqLevel3, TRUE);
#endif
#if 1
	Display();
	while(1)		//主控板程序
	{
		Message();
	}
#endif
}

static void App_UserKeyInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    //< 打开GPIO外设时钟门控
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    //< 端口方向配置->输入
    stcGpioCfg.enDir = GpioDirIn;
    //< 端口驱动能力配置->高驱动能力
    stcGpioCfg.enDrv = GpioDrvL;
    //< 端口上下拉配置->无
    stcGpioCfg.enPu = GpioPuEnable;
    stcGpioCfg.enPd = GpioPdDisable;
    //< 端口开漏输出配置->开漏输出关闭
    stcGpioCfg.enOD = GpioOdDisable;
    //< 端口输入/输出值寄存器总线控制模式配置->AHB
    stcGpioCfg.enCtrlMode = GpioAHB;
    //< GPIO IO USER KEY初始化
    Gpio_Init(STK_USER_PORT, STK_USER_PIN, &stcGpioCfg); 
}

static void App_BeeInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    
    //< 打开GPIO外设时钟门控
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
    
    //< 端口方向配置->输出(其它参数与以上（输入）配置参数一致)
    stcGpioCfg.enDir = GpioDirOut;
    //< 端口上下拉配置->下拉
    stcGpioCfg.enPu = GpioPuEnable;
    stcGpioCfg.enPd = GpioPdDisable;
    stcGpioCfg.enDrv = GpioDrvH;
    
    //< GPIO IO Bee端口初始化
    Gpio_Init(STK_BEE_PORT, STK_BEE_PIN, &stcGpioCfg);
    //< Bee关闭
	Gpio_SetIO(STK_BEE_PORT, STK_BEE_PIN);
}    

void PortA_IRQHandler(void)
{
}

void Bee(void)
{
	
}

/******************************************************************************
 * EOF (not truncated)						//25216969
//        if(FALSE != Gpio_GetInputIO(STK_USER_PORT, STK_USER_PIN1))
//			StateNumber=1;
 ******************************************************************************/

