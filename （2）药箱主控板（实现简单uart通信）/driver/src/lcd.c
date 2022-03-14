/******************************************************************************
* Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \file lcd.c
 **
 ** lcd driver API.
 **
 **   - 2019-04-02    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "lcd.h"
#include "gpio.h"
#include "rtc.h"
#include "stddef.h"

/**
 ******************************************************************************
 ** \addtogroup AdcGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#if 0
#define	S1on	Lcd_WriteRam(1,0x00000800)
#define	S1off	Lcd_CleanRamBit(1,0xFFFFF7FF)
#define	S2on	Lcd_WriteRam(2,0x00000200)
#define	S2off	Lcd_CleanRamBit(2,0xFFFFFDFF)
#define	S3on	Lcd_WriteRam(1,0x00000100)
#define	S3off	Lcd_CleanRamBit(1,0xFFFFFEFF)
#define	S4on	Lcd_WriteRam(3,0x00000100)
#define	S4off	Lcd_CleanRamBit(3,0xFFFFFEFF)
#define	S5on	Lcd_WriteRam(1,0x00010000)
#define	S5off	Lcd_CleanRamBit(1,0xFFFEFFFF)
#define	S6on	Lcd_WriteRam(2,0x00000001)
#define	S6off	Lcd_CleanRamBit(2,0xFFFFFFFE)
#define	S7on	Lcd_WriteRam(2,0x00000100)
#define	S7off	Lcd_CleanRamBit(2,0xFFFFFEFF)
#define	S8on	Lcd_WriteRam(2,0x01000000)
#define	S8off	Lcd_CleanRamBit(2,0xFEFFFFFF)
#define	S9on	Lcd_WriteRam(3,0x00000001)
#define	S9off	Lcd_CleanRamBit(3,0xFFFFFFFE)
#endif
/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
uint8_t DisplayBuff[12];	
stc_rtc_time_t RtcTime;	//
stc_rtc_alarmtime_t Clock1,Clock2,Clock3,Clock4,Clock5;	//
/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
 /**
 ******************************************************************************
 ** \brief  配置LCD
 **
 ** \return 无
 ******************************************************************************/
void App_LcdCfg(void)
{
    stc_lcd_cfg_t LcdInitStruct;
    stc_lcd_segcom_t LcdSegCom;

    LcdSegCom.u32Seg0_31 = 0xfe000000;                 //< 配置LCD_POEN0寄存器 开启SEG0~SEG7
    LcdSegCom.stc_seg32_51_com0_8_t.seg32_51_com0_8 = 0xfffff0ff;            //< 初始化LCD_POEN1寄存器 全部关闭输出端口
    LcdSegCom.stc_seg32_51_com0_8_t.segcom_bit.Com0_3 = 0;           //< 使能COM0~COM3
    LcdSegCom.stc_seg32_51_com0_8_t.segcom_bit.Mux = 0;          //< Mux=0,Seg32_35=0,BSEL=1表示:选择外部电容工作模式，内部电阻断路
    LcdSegCom.stc_seg32_51_com0_8_t.segcom_bit.Seg32_35 = 0;			//
    Lcd_SetSegCom(&LcdSegCom);                                   //< LCD COMSEG端口配置

    LcdInitStruct.LcdBiasSrc = LcdExtCap;                          //< 电容分压模式，需要外部电路配合
    LcdInitStruct.LcdDuty = LcdDuty4;                              //< 1/4duty
    LcdInitStruct.LcdBias = LcdBias3;                              //< 1/3 BIAS
    LcdInitStruct.LcdCpClk = LcdClk2k;                             //< 电压泵时钟频率选择2kHz
    LcdInitStruct.LcdScanClk = LcdClk128hz;                        //< LCD扫描频率选择128Hz
    LcdInitStruct.LcdMode = LcdMode1;                              //< 选择模式1
    LcdInitStruct.LcdClkSrc = LcdRCL;                              //< LCD时钟选择RCL
    LcdInitStruct.LcdEn   = LcdEnable;                             //< 使能LCD模块
    Lcd_Init(&LcdInitStruct);

}

/********************************************************************************
 ** \brief  初始化外部GPIO引脚
 **
 ** \return 无
 ******************************************************************************/
void App_PortCfg(void)
{
    Gpio_SetAnalogMode(STK_LCD_COM0_PORT, STK_LCD_COM0_PIN);  //COM0
    Gpio_SetAnalogMode(STK_LCD_COM1_PORT, STK_LCD_COM1_PIN); //COM1
    Gpio_SetAnalogMode(STK_LCD_COM2_PORT, STK_LCD_COM2_PIN);  //COM2
    Gpio_SetAnalogMode(STK_LCD_COM3_PORT, STK_LCD_COM3_PIN); //COM3

    Gpio_SetAnalogMode(STK_LCD_SEG0_PORT, STK_LCD_SEG0_PIN);  //SEG0
    Gpio_SetAnalogMode(STK_LCD_SEG1_PORT, STK_LCD_SEG1_PIN);  //SEG1
    Gpio_SetAnalogMode(STK_LCD_SEG2_PORT, STK_LCD_SEG2_PIN);  //SEG2
    Gpio_SetAnalogMode(STK_LCD_SEG3_PORT, STK_LCD_SEG3_PIN);  //SEG3
    Gpio_SetAnalogMode(STK_LCD_SEG4_PORT, STK_LCD_SEG4_PIN);  //SEG4
    Gpio_SetAnalogMode(STK_LCD_SEG5_PORT, STK_LCD_SEG5_PIN);  //SEG5
    Gpio_SetAnalogMode(STK_LCD_SEG6_PORT, STK_LCD_SEG6_PIN);  //SEG6
    Gpio_SetAnalogMode(STK_LCD_SEG7_PORT, STK_LCD_SEG7_PIN);  //SEG7
    Gpio_SetAnalogMode(STK_LCD_SEG8_PORT, STK_LCD_SEG8_PIN);  //SEG8
    Gpio_SetAnalogMode(STK_LCD_SEG9_PORT, STK_LCD_SEG9_PIN);  //SEG9
    Gpio_SetAnalogMode(STK_LCD_SEG10_PORT, STK_LCD_SEG10_PIN);  //SEG10
    Gpio_SetAnalogMode(STK_LCD_SEG11_PORT, STK_LCD_SEG11_PIN);  //SEG11
    Gpio_SetAnalogMode(STK_LCD_SEG12_PORT, STK_LCD_SEG12_PIN);  //SEG12
    Gpio_SetAnalogMode(STK_LCD_SEG13_PORT, STK_LCD_SEG13_PIN);  //SEG13
    Gpio_SetAnalogMode(STK_LCD_SEG14_PORT, STK_LCD_SEG14_PIN);  //SEG14
    Gpio_SetAnalogMode(STK_LCD_SEG15_PORT, STK_LCD_SEG15_PIN);  //SEG15
    Gpio_SetAnalogMode(STK_LCD_SEG16_PORT, STK_LCD_SEG16_PIN);  //SEG16
    Gpio_SetAnalogMode(STK_LCD_SEG17_PORT, STK_LCD_SEG17_PIN);  //SEG17
    Gpio_SetAnalogMode(STK_LCD_SEG18_PORT, STK_LCD_SEG18_PIN);  //SEG18
    Gpio_SetAnalogMode(STK_LCD_SEG19_PORT, STK_LCD_SEG19_PIN);  //SEG19
    Gpio_SetAnalogMode(STK_LCD_SEG20_PORT, STK_LCD_SEG20_PIN);  //SEG20
    Gpio_SetAnalogMode(STK_LCD_SEG21_PORT, STK_LCD_SEG21_PIN);  //SEG21
    Gpio_SetAnalogMode(STK_LCD_SEG22_PORT, STK_LCD_SEG22_PIN);  //SEG22
    Gpio_SetAnalogMode(STK_LCD_SEG23_PORT, STK_LCD_SEG23_PIN);  //SEG23
    Gpio_SetAnalogMode(STK_LCD_SEG24_PORT, STK_LCD_SEG24_PIN);  //SEG24

    Gpio_SetAnalogMode(STK_VLCDH_PORT, STK_VLCDH_PIN);  //VLCDH
    Gpio_SetAnalogMode(STK_VLCD1_PORT, STK_VLCD1_PIN);  //VLCD1
    Gpio_SetAnalogMode(STK_VLCD2_PORT, STK_VLCD2_PIN);  //VLCD2
    Gpio_SetAnalogMode(STK_VLCD3_PORT, STK_VLCD3_PIN);  //VLCD3
}

/********************************************************************************
    ** \brief  获取LCD中断标志位INTF
    ** 
    ** @param  无
    ** \retval 无
    **
******************************************************************************/
boolean_t Lcd_GetItStatus(void)
{
	return (((M0P_LCD->CR1)>>11)&0x01)? TRUE : FALSE;
}

/********************************************************************************
    ** \brief  清除中断标志位INTF
    ** 
    ** @param  无
    ** \retval 无
    **
******************************************************************************/
void Lcd_ClearItPendingBit(void)
{
	SetBit((uint32_t)(&(M0P_LCD->INTCLR)), 10, 0);
}

/**
******************************************************************************
    ** \brief  根据LCD显示模式获取端口配置
    **
    ** \param pstcSegComPara：显示方式， stcSegCom获取端口参数
    **
    ** \retval enRet 成功或失败
    **
******************************************************************************/
en_result_t Lcd_GetSegCom(stc_lcd_segcompara_t *pstcSegComPara,stc_lcd_segcom_t *pstcSegCom)
{
	en_result_t enRet = Error;
	pstcSegCom->stc_seg32_51_com0_8_t.seg32_51_com0_8 = 0xffffffffu;
	pstcSegCom->u32Seg0_31                            = 0xffffffffu;
	if(pstcSegComPara->u8MaxSeg>51)
	{
		return ErrorInvalidParameter;
	}
    switch(pstcSegComPara->LcdBiasSrc)
    {
        case LcdInResHighPower:
        case LcdInResLowPower:
        case LcdInResMidPower:
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Mux = 1;
            break;
        case LcdExtCap:
        case LcdExtRes:
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Mux = 0;
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Seg32_35 = 0;
            break;
        default:
            return ErrorInvalidParameter;
    }
    switch(pstcSegComPara->LcdDuty)
    {
        case LcdStatic:
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Com0_3 = (~1u)&0x0fu;
            break;
        case LcdDuty2:
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Com0_3 = (~3u)&0x0fu;
            break;
        case LcdDuty3:
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Com0_3 = (~7u)&0x0fu;
            break;
        case LcdDuty4:
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Com0_3 = (~15u)&0x0fu;
            break;
        case LcdDuty6:
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Com0_3 = 0;
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Seg39Com4 = 0;
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Seg38Com5 = 0;
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Seg37Com6 = 1;
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Seg36Com7 = 1;
            break;
        case LcdDuty8:
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Com0_3 = 0;
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Seg39Com4 = 0;
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Seg38Com5 = 0;
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Seg37Com6 = 0;
            pstcSegCom->stc_seg32_51_com0_8_t.segcom_bit.Seg36Com7 = 0;
                break;            
        default:
            return ErrorInvalidParameter;
    }
    enRet = Ok;
    return enRet;
}

/**
******************************************************************************
    ** \brief  LCD COMSEG端口配置，使用该函数之前需要先使能相应的Seg
    **
    ** \param [in] pstcSegCom端口配置结构体
    **
    ** \retval enRet 成功或失败
    **
******************************************************************************/
void Lcd_SetSegCom(stc_lcd_segcom_t *pstcSegCom)
{
    M0P_LCD->POEN0 = pstcSegCom->u32Seg0_31;
    M0P_LCD->POEN1 = pstcSegCom->stc_seg32_51_com0_8_t.seg32_51_com0_8;
}

/**
******************************************************************************
    ** \brief  LCD模块初始化函数
    **
    ** \param stcLcdCfg配置初始化结构体
    **
    ** \retval 无
    **
******************************************************************************/
void Lcd_Init(stc_lcd_cfg_t *pstcLcdCfg)
{
    M0P_LCD->CR0_f.BSEL   = pstcLcdCfg->LcdBiasSrc;
    M0P_LCD->CR0_f.DUTY   = pstcLcdCfg->LcdDuty;
    M0P_LCD->CR0_f.BIAS   = pstcLcdCfg->LcdBias;
    M0P_LCD->CR0_f.CPCLK  = pstcLcdCfg->LcdCpClk;
    M0P_LCD->CR0_f.LCDCLK = pstcLcdCfg->LcdScanClk;
    M0P_LCD->CR1_f.MODE   = pstcLcdCfg->LcdMode;
    M0P_LCD->CR1_f.CLKSRC = pstcLcdCfg->LcdClkSrc;
    M0P_LCD->CR0_f.EN     = pstcLcdCfg->LcdEn;
}

/**
******************************************************************************
    ** \brief  液晶全显
    **
    ** \param  无
    **
    ** \retval 无
    **
******************************************************************************/
void Lcd_FullDisp(void)
{
    uint8_t tmp;
    volatile uint32_t *ram = NULL;
    ram = &M0P_LCD->RAM0;
    for(tmp=0;tmp<16;tmp++)
    {
        *ram = 0xffffffffu;
        ram++;
    }
}

/**
******************************************************************************
    ** \brief  清屏
    **
    ** \param 无
    **
    ** \retval 无
    **
******************************************************************************/
void Lcd_ClearDisp(void)
{
    uint8_t tmp;
    volatile uint32_t *ram = NULL;
    ram = &M0P_LCD->RAM0;
    for(tmp=0;tmp<16;tmp++)
    {
            *ram = 0;
            ram++;
    }
}

/**
 ******************************************************************************
 ** \brief  LCD RAM 0-f寄存器设置函数
 **
 ** \param u8Row RAM地址索引，范围：0-15，u8Data写入寄存器数值
 **
 ** \retval enRet 成功或失败
 **
 ******************************************************************************/
en_result_t Lcd_WriteRam(uint8_t u8Row,uint32_t u32Data)
{
    en_result_t  enRet = Error;
    volatile uint32_t *ram = NULL;
    ram = (volatile uint32_t*)&M0P_LCD->RAM0;

    if (u8Row > 15)
    {
        enRet = ErrorInvalidParameter;
        return enRet;
    }
    
    ram += u8Row;
    *ram |= u32Data;
    enRet = Ok;
    return  enRet; 
}
en_result_t Lcd_CleanRamBit(uint8_t u8Row,uint32_t u32Data)
{
    en_result_t  enRet = Error;
    volatile uint32_t *ram = NULL;
    ram = (volatile uint32_t*)&M0P_LCD->RAM0;

    if (u8Row > 15)
    {
        enRet = ErrorInvalidParameter;
        return enRet;
    }
    
    ram += u8Row;
    *ram &= u32Data;
    enRet = Ok;
    return  enRet; 
}

/****************************************************************************/
#if 0
void TimerDisplay(uint8_t *Number,uint8_t State)
{
	uint8_t i;
	switch(State)
	{
		case	0:
			Rtc_ReadDateTime(&RtcTime);
			
			Number[0]=	(BCD2DEC(RtcTime.u8Hour)/10)%10;//
			Number[1]=	BCD2DEC(RtcTime.u8Hour)%10;//
			
			Number[2]=	(BCD2DEC(RtcTime.u8Minute)/10)%10;//
			Number[3]=	BCD2DEC(RtcTime.u8Minute)%10;//
			
			if((BCD2DEC(RtcTime.u8Second)%10)%2)
				S2on;
			else
				S2off;
			break;
		case	1:
			S2on;
			if((BCD2DEC(RtcTime.u8Second)%10)%2)
			{
				if(ModifyNumber==1)
				{
					Number[0]=	(BCD2DEC(Clock1.RtcAlarmHour)/10)%10;//
					Number[1]=	BCD2DEC(Clock1.RtcAlarmHour)%10;//
					Number[2]=0x0a;
					Number[3]=0x0a;
				}
				if(ModifyNumber==2)
				{
					Number[0]=0x0a;
					Number[1]=0x0a;
					Number[2]=	(BCD2DEC(Clock1.RtcAlarmMinute)/10)%10;//
					Number[3]=	BCD2DEC(Clock1.RtcAlarmMinute)%10;//
				}
			}
			else
			{
				Number[0]=	(BCD2DEC(Clock1.RtcAlarmHour)/10)%10;//
				Number[1]=	BCD2DEC(Clock1.RtcAlarmHour)%10;//
				Number[2]=	(BCD2DEC(Clock1.RtcAlarmMinute)/10)%10;//
				Number[3]=	BCD2DEC(Clock1.RtcAlarmMinute)%10;//
			}
			break;
		case	2:
			S2on;
			Number[0]=	(BCD2DEC(Clock2.RtcAlarmHour)/10)%10;//
			Number[1]=	BCD2DEC(Clock2.RtcAlarmHour)%10;//
			Number[2]=	(BCD2DEC(Clock2.RtcAlarmMinute)/10)%10;//
			Number[3]=	BCD2DEC(Clock2.RtcAlarmMinute)%10;//
			if((BCD2DEC(RtcTime.u8Second)%10)%2)
			{
				if(ModifyNumber==1)
				{
					Number[2]=0x0a;
					Number[3]=0x0a;
				}
				if(ModifyNumber==2)
				{
					Number[0]=0x0a;
					Number[1]=0x0a;
				}
			}
			break;
		case	3:
			S2on;
			Number[0]=	(BCD2DEC(Clock3.RtcAlarmHour)/10)%10;//
			Number[1]=	BCD2DEC(Clock3.RtcAlarmHour)%10;//
			Number[2]=	(BCD2DEC(Clock3.RtcAlarmMinute)/10)%10;//
			Number[3]=	BCD2DEC(Clock3.RtcAlarmMinute)%10;//
			if((BCD2DEC(RtcTime.u8Second)%10)%2)
			{
				if(ModifyNumber==1)
				{
					Number[2]=0x0a;
					Number[3]=0x0a;
				}
				if(ModifyNumber==2)
				{
					Number[0]=0x0a;
					Number[1]=0x0a;
				}
			}
			break;
		case	4:
			S2on;
			Number[0]=	(BCD2DEC(Clock4.RtcAlarmHour)/10)%10;//
			Number[1]=	BCD2DEC(Clock4.RtcAlarmHour)%10;//
			Number[2]=	(BCD2DEC(Clock4.RtcAlarmMinute)/10)%10;//
			Number[3]=	BCD2DEC(Clock4.RtcAlarmMinute)%10;//
			if((BCD2DEC(RtcTime.u8Second)%10)%2)
			{
				if(ModifyNumber==1)
				{
					Number[2]=0x0a;
					Number[3]=0x0a;
				}
				if(ModifyNumber==2)
				{
					Number[0]=0x0a;
					Number[1]=0x0a;
				}
			}
			break;
		case	5:
			S2on;
			Number[0]=	(BCD2DEC(Clock5.RtcAlarmHour)/10)%10;//
			Number[1]=	BCD2DEC(Clock5.RtcAlarmHour)%10;//
			Number[2]=	(BCD2DEC(Clock5.RtcAlarmMinute)/10)%10;//
			Number[3]=	BCD2DEC(Clock5.RtcAlarmMinute)%10;//
			if((BCD2DEC(RtcTime.u8Second)%10)%2)
			{
				if(ModifyNumber==1)
				{
					Number[2]=0x0a;
					Number[3]=0x0a;
				}
				if(ModifyNumber==2)
				{
					Number[0]=0x0a;
					Number[1]=0x0a;
				}
			}
			break;
		default:
			break;
	}	
	for(i=0;i<4;i++)
	{
		switch(i)
		{
			case 0x00:
				switch(*Number)
				{
					case 0x00:
						Lcd_CleanRamBit(1,0xF3F1FDFF);
						break;
					case 0x01:
						Lcd_CleanRamBit(1,0xF7F3FDFF);
						Lcd_WriteRam(1,0x04020000);
						break;
					case 0x02:
						Lcd_CleanRamBit(1,0xFBFFFFFF);
						Lcd_WriteRam(1,0x080E0200);
						break;
					case 0x0a:
						Lcd_CleanRamBit(1,0xF3F1FDFF);
						break;
					default:
						break;
				}
				break;
			case 0x01:
				switch(*Number)
				{
					case 0x00:
						Lcd_CleanRamBit(2,0xFFFFFFFB);
						Lcd_WriteRam(1,0x03000000);
						Lcd_WriteRam(2,0x00000C0A);
						break;
					case 0x01:
						Lcd_CleanRamBit(1,0xFCFFFFFF);
						Lcd_CleanRamBit(2,0xFFFFF7F3);
						Lcd_WriteRam(2,0x00000402);
						break;
					case 0x02:
						Lcd_CleanRamBit(1,0xFDFFFFFF);
						Lcd_CleanRamBit(2,0xFFFFFBFF);
						Lcd_WriteRam(1,0x01000000);
						Lcd_WriteRam(2,0x0000080E);
						break;
					case 0x03:
						Lcd_CleanRamBit(1,0xFDFFFFFF);
						Lcd_CleanRamBit(2,0xFFFFFFF7);
						Lcd_WriteRam(1,0x01000000);
						Lcd_WriteRam(2,0x00000C06);
						break;
					case 0x04:
						Lcd_CleanRamBit(1,0xFEFFFFFF);
						Lcd_CleanRamBit(2,0xFFFFF7F7);
						Lcd_WriteRam(1,0x02000000);
						Lcd_WriteRam(2,0x00000406);
						break;
					case 0x05:
						Lcd_CleanRamBit(2,0xFFFFFFF5);
						Lcd_WriteRam(1,0x03000000);
						Lcd_WriteRam(2,0x00000C04);
						break;
					case 0x06:
						Lcd_CleanRamBit(2,0xFFFFFFFD);
						Lcd_WriteRam(1,0x03000000);
						Lcd_WriteRam(2,0x00000C0C);
						break;
					case 0x07:
						Lcd_CleanRamBit(1,0xFDFFFFFF);
						Lcd_CleanRamBit(2,0xFFFFF7F3);
						Lcd_WriteRam(1,0x01000000);
						Lcd_WriteRam(2,0x00000402);
						break;
					case 0x08:
						Lcd_WriteRam(1,0x03000000);
						Lcd_WriteRam(2,0x00000C0E);
						break;
					case 0x09:
						Lcd_CleanRamBit(2,0xFFFFFFF7);
						Lcd_WriteRam(1,0x03000000);
						Lcd_WriteRam(2,0x00000C06);
						break;
					case 0x0a:
						Lcd_CleanRamBit(1,0xFCFFFFFF);
						Lcd_CleanRamBit(2,0xFFFFF3F1);
						break;
					default:
						break;
				}
				break;
			case 0x02:
				switch(*Number)
				{
					case 0x00:
						Lcd_CleanRamBit(2,0xFFFBFFFF);
						Lcd_WriteRam(2,0x0A0B0000);
						break;
					case 0x01:
						Lcd_CleanRamBit(2,0xFFF0FFFF);
						Lcd_WriteRam(2,0x0A000000);
						break;
					case 0x02:
						Lcd_CleanRamBit(2,0xF7FDFFFF);
						Lcd_WriteRam(2,0x020D0000);
						break;
					case 0x03:
						Lcd_CleanRamBit(2,0xFFF5FFFF);
						Lcd_WriteRam(2,0x0A050000);
						break;
					case 0x04:
						Lcd_CleanRamBit(2,0xFFF6FFFF);
						Lcd_WriteRam(2,0x0A060000);
						break;
					case 0x05:
						Lcd_CleanRamBit(2,0xFDF7FFFF);
						Lcd_WriteRam(2,0x08070000);
						break;
					case 0x0a:
						Lcd_CleanRamBit(2,0xF5F0FFFF);
						break;
					default:
						break;
				}
				break;
			case 0x03:
				switch(*Number)
				{
					case 0x00:
						Lcd_CleanRamBit(3,0xFFFFFFFB);
						Lcd_WriteRam(2,0x04000000);
						Lcd_WriteRam(3,0x00000E0A);
						break;
					case 0x01:
						Lcd_CleanRamBit(2,0xFBFFFFFF);
						Lcd_CleanRamBit(3,0xFFFFF7F1);
						Lcd_WriteRam(3,0x00000600);
						break;
					case 0x02:
						Lcd_CleanRamBit(2,0xFBFFFFFF);
						Lcd_CleanRamBit(3,0xFFFFFBFF);
						Lcd_WriteRam(3,0x00000A0E);
						break;
					case 0x03:
						Lcd_CleanRamBit(2,0xFBFFFFFF);
						Lcd_CleanRamBit(3,0xFFFFFFF7);
						Lcd_WriteRam(3,0x00000E06);
						break;
					case 0x04:
						Lcd_CleanRamBit(3,0xFFFFF7F5);
						Lcd_WriteRam(2,0x04000000);
						Lcd_WriteRam(3,0x00000604);
						break;
					case 0x05:
						Lcd_CleanRamBit(3,0xFFFFFDF7);
						Lcd_WriteRam(2,0x04000000);
						Lcd_WriteRam(3,0x00000C06);
						break;
					case 0x06:
						Lcd_CleanRamBit(3,0xFFFFFDFF);
						Lcd_WriteRam(2,0x04000000);
						Lcd_WriteRam(3,0x00000C0E);
						break;
					case 0x07:
						Lcd_CleanRamBit(2,0xFBFFFFFF);
						Lcd_CleanRamBit(3,0xFFFFF7F3);
						Lcd_WriteRam(3,0x00000602);
						break;
					case 0x08:
						Lcd_WriteRam(2,0x04000000);
						Lcd_WriteRam(3,0x00000E0E);
						break;
					case 0x09:
						Lcd_CleanRamBit(3,0xFFFFFFF7);
						Lcd_WriteRam(2,0x04000000);
						Lcd_WriteRam(3,0x00000E06);
						break;
					case 0x0a:
						Lcd_CleanRamBit(2,0xFBFFFFFF);
						Lcd_CleanRamBit(3,0xFFFFF1F1);
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
		Number++;
	}
}
#endif

