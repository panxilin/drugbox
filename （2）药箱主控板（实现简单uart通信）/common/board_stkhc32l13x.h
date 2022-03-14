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
/** \file stkhc32l13x.h
 **
 ** stk board common define.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2018-03-09  1.0  Lux First version.
 **
 ******************************************************************************/
#ifndef __BOARD_STKHC32L13X_H__
#define __BOARD_STKHC32L13X_H__

//< STK GPIO DEFINE
//< USER KEY
#define STK_USER_PORT       GpioPortD
#define STK_USER_PIN        GpioPin2

//< Bee
#define STK_BEE_PORT        GpioPortD
#define STK_BEE_PIN         GpioPin4

//< XTH
#define SYSTEM_XTH          (32*1000*1000u)     //< 32MHz

#define STK_XTHI_PORT       GpioPortD
#define STK_XTHI_PIN        GpioPin0
#define STK_XTHO_PORT       GpioPortD
#define STK_XTHO_PIN        GpioPin1

//< XTL
#define SYSTEM_XTL          (32768u)            //< 32768Hz
#define STK_XTLI_PORT       GpioPortC
#define STK_XTLI_PIN        GpioPin14
#define STK_XTLO_PORT       GpioPortC
#define STK_XTLO_PIN        GpioPin15

//< LCD
#define STK_LCD_COM0_PORT   GpioPortA
#define STK_LCD_COM0_PIN    GpioPin9
#define STK_LCD_COM1_PORT   GpioPortA
#define STK_LCD_COM1_PIN    GpioPin10
#define STK_LCD_COM2_PORT   GpioPortA
#define STK_LCD_COM2_PIN    GpioPin11
#define STK_LCD_COM3_PORT   GpioPortA
#define STK_LCD_COM3_PIN    GpioPin12

#define STK_LCD_SEG0_PORT   GpioPortA
#define STK_LCD_SEG0_PIN    GpioPin8
#define STK_LCD_SEG1_PORT   GpioPortC
#define STK_LCD_SEG1_PIN    GpioPin9
#define STK_LCD_SEG2_PORT   GpioPortC
#define STK_LCD_SEG2_PIN    GpioPin8
#define STK_LCD_SEG3_PORT   GpioPortC
#define STK_LCD_SEG3_PIN    GpioPin7
#define STK_LCD_SEG4_PORT   GpioPortC
#define STK_LCD_SEG4_PIN    GpioPin6
#define STK_LCD_SEG5_PORT   GpioPortB
#define STK_LCD_SEG5_PIN    GpioPin15
#define STK_LCD_SEG6_PORT   GpioPortB
#define STK_LCD_SEG6_PIN    GpioPin14
#define STK_LCD_SEG7_PORT   GpioPortB
#define STK_LCD_SEG7_PIN    GpioPin13
#define STK_LCD_SEG8_PORT   GpioPortB
#define STK_LCD_SEG8_PIN    GpioPin12
#define STK_LCD_SEG9_PORT   GpioPortB
#define STK_LCD_SEG9_PIN    GpioPin11
#define STK_LCD_SEG10_PORT   GpioPortB
#define STK_LCD_SEG10_PIN    GpioPin10
#define STK_LCD_SEG11_PORT   GpioPortB
#define STK_LCD_SEG11_PIN    GpioPin2
#define STK_LCD_SEG12_PORT   GpioPortB
#define STK_LCD_SEG12_PIN    GpioPin1
#define STK_LCD_SEG13_PORT   GpioPortB
#define STK_LCD_SEG13_PIN    GpioPin0
#define STK_LCD_SEG14_PORT   GpioPortC
#define STK_LCD_SEG14_PIN    GpioPin5
#define STK_LCD_SEG15_PORT   GpioPortC
#define STK_LCD_SEG15_PIN    GpioPin4
#define STK_LCD_SEG16_PORT   GpioPortA
#define STK_LCD_SEG16_PIN    GpioPin7
#define STK_LCD_SEG17_PORT   GpioPortA
#define STK_LCD_SEG17_PIN    GpioPin6
#define STK_LCD_SEG18_PORT   GpioPortA
#define STK_LCD_SEG18_PIN    GpioPin5
#define STK_LCD_SEG19_PORT   GpioPortA
#define STK_LCD_SEG19_PIN    GpioPin4
#define STK_LCD_SEG20_PORT   GpioPortA
#define STK_LCD_SEG20_PIN    GpioPin3
#define STK_LCD_SEG21_PORT   GpioPortA
#define STK_LCD_SEG21_PIN    GpioPin2
#define STK_LCD_SEG22_PORT   GpioPortA
#define STK_LCD_SEG22_PIN    GpioPin1
#define STK_LCD_SEG23_PORT   GpioPortA
#define STK_LCD_SEG23_PIN    GpioPin0
#define STK_LCD_SEG24_PORT   GpioPortC
#define STK_LCD_SEG24_PIN    GpioPin3

#define STK_VLCDH_PORT    GpioPortB
#define STK_VLCDH_PIN    GpioPin3
#define STK_VLCD3_PORT    GpioPortB
#define STK_VLCD3_PIN    GpioPin4
#define STK_VLCD2_PORT    GpioPortB
#define STK_VLCD2_PIN    GpioPin5
#define STK_VLCD1_PORT    GpioPortB
#define STK_VLCD1_PIN    GpioPin6

//< I2C GXHT30
#define STK_I2C1_SCL_PORT    GpioPortD
#define STK_I2C1_SCL_PIN     GpioPin6
#define STK_I2C1_SDA_PORT    GpioPortD
#define STK_I2C1_SDA_PIN     GpioPin7

//< UART CC3200
#define STK_UART0_TXD_PORT	GpioPortB
#define STK_UART0_TXD_PIN	GpioPin8
#define STK_UART0_RXD_PORT	GpioPortB
#define STK_UART0_RXD_PIN	GpioPin9

#endif
