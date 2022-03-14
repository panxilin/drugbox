#include "crd7601.h"
#include "lcd.h"
#include "base_types.h"

en_result_t Lcd_WriteRam(uint8_t u8Row,uint32_t u32Data);

void Display(void)
{
	Lcd_WriteRam(0,0xffffffff);
	Lcd_WriteRam(1,0xffffffff);
	Lcd_WriteRam(2,0xffffffff);
	Lcd_WriteRam(3,0xffffffff);
}
