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
 ** \brief  ?????????
 ** 
 ** @param  ???
 ** \retval ???
 **
 ******************************************************************************/ 
int32_t main(void)
{	
#if 1	//???????????????
//	uint16_t i=0,j=0;
	Sysctrl_ClkSourceEnable(SysctrlClkRCL,TRUE);            //< ??????RCL??????
	Sysctrl_SetRCLTrim(SysctrlRclFreq32768);                //< ?????????????????????????????????32.768kHz
	Sysctrl_SetPeripheralGate(SysctrlPeripheralLcd,TRUE);   //< ??????LCD??????
	App_LcdCfg();				//< LCD????????????
	App_PortCfg();				//<LCD????????????
	App_BeeInit();				//<??????????????????
	App_RtcCfg();				//<RTC???????????????			
	App_ClkCfg();				//<????????????
	App_UserKeyInit();			//<???????????????	
	App_PortInit();				//<UART?????????
	App_UartCfg();				//<UART??????
	Rtc_Cmd(TRUE);  			//<??????RTC??????
    EnableNvic(PORTA_IRQn, IrqLevel3, TRUE);
#endif
#if 1
	Display();
	while(1)		//???????????????
	{
		Message();
	}
#endif
}

static void App_UserKeyInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    //< ??????GPIO??????????????????
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    //< ??????????????????->??????
    stcGpioCfg.enDir = GpioDirIn;
    //< ????????????????????????->???????????????
    stcGpioCfg.enDrv = GpioDrvL;
    //< ?????????????????????->???
    stcGpioCfg.enPu = GpioPuEnable;
    stcGpioCfg.enPd = GpioPdDisable;
    //< ????????????????????????->??????????????????
    stcGpioCfg.enOD = GpioOdDisable;
    //< ????????????/??????????????????????????????????????????->AHB
    stcGpioCfg.enCtrlMode = GpioAHB;
    //< GPIO IO USER KEY?????????
    Gpio_Init(STK_USER_PORT, STK_USER_PIN, &stcGpioCfg); 
}

static void App_BeeInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    
    //< ??????GPIO??????????????????
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
    
    //< ??????????????????->??????(???????????????????????????????????????????????????)
    stcGpioCfg.enDir = GpioDirOut;
    //< ?????????????????????->??????
    stcGpioCfg.enPu = GpioPuEnable;
    stcGpioCfg.enPd = GpioPdDisable;
    stcGpioCfg.enDrv = GpioDrvH;
    
    //< GPIO IO Bee???????????????
    Gpio_Init(STK_BEE_PORT, STK_BEE_PIN, &stcGpioCfg);
    //< Bee??????
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

