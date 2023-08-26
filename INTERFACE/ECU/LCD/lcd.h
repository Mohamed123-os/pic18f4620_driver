/* 
 * File:   lcd.h
 * Author: mohamed
 *
 * Created on August 17, 2023, 7:41 PM
 */

#ifndef LCD_H
#define	LCD_H

/***************************includes section****************************************/
#include"../../MCAL/GPIO/gpio.h"
/***************************macros sections*****************************************/
#define LCD_CLEAR                  0X01
#define LCD_RETURN_HOME            0X02

#define LCD_CURSOR_ON_DISPLAY_ON   0X0F
#define LCD_CURSOR_OFF_DISPLAY_ON  0X0C

#define LCD_CURSOR_OFF_DISPLAY_OFF  0X08
#define LCD_CURSOR_ON_DISPLAY_OFF   0X0C

#define LCD_CURSOR_BLINK            0X09
#define LCD_CURSOR_NOT_BLINK        0X08

#define SHIFT_CURSOR_LEFT           0X10
#define SHIFT_CURSOR_RIGHT          0X14

#define SHIFT_ENTIRE_DISPLAY_LEFT   0X18
#define SHIFT_ENTIRE_DISPLAY_RIGHT  0X1C

#define _LCD_8BIT_MODE_2_LINE       0x38
#define _LCD_4BIT_MODE_2_LINE       0x28

#define _LCD_CGRAM_START            0x40
#define _LCD_DDRAM_START            0x80

#define ROW1                         1
#define ROW2                         2
#define ROW3                         3
#define ROW4                         4


/***************************function like macro section*****************************/
/***************************data types section**************************************/
typedef struct{
    pin_config rs;
    pin_config en;
    pin_config _4_bit[4];
    
}lcd_4_bit_mode;

typedef struct{
    pin_config rs;
    pin_config en;
    pin_config _8_bit[8];
    
}lcd_8_bit_mode;
/***************************software interfaces section*****************************/
Std_ReturnType   lcd_4_bit_init(const lcd_4_bit_mode *lcd);
Std_ReturnType   send_command(const lcd_4_bit_mode *lcd, uint8 command);
Std_ReturnType   display_char (const lcd_4_bit_mode *lcd,uint8 data);
Std_ReturnType   display_char_at_position (const lcd_4_bit_mode *lcd,uint8 row,uint8 coloumn,uint8 data);
Std_ReturnType   display_string (const lcd_4_bit_mode *lcd,uint8 *data);
Std_ReturnType   display_string_at_position (const lcd_4_bit_mode *lcd,uint8 row,uint8 coloumn,uint8 *data);
Std_ReturnType   display_custom_char(const lcd_4_bit_mode *lcd, uint8 row, uint8 cloumn , uint8 data[],uint8 mem_pos);




Std_ReturnType   lcd_8_bit_init(const lcd_8_bit_mode *lcd);
Std_ReturnType   send_command_8(const lcd_8_bit_mode *lcd, uint8 command);
Std_ReturnType   display_char_8 (const lcd_8_bit_mode *lcd,uint8 data);
Std_ReturnType   display_char_at_position_8 (const lcd_8_bit_mode *lcd,uint8 row,uint8 coloumn,uint8 data);
Std_ReturnType   display_string_8 (const lcd_8_bit_mode *lcd,uint8 *data);
Std_ReturnType   display_string_at_position_8 (const lcd_8_bit_mode *lcd,uint8 row,uint8 coloumn,uint8 *data);
Std_ReturnType   display_custom_char_8(const lcd_8_bit_mode *lcd, uint8 row, uint8 cloumn , uint8 data[],uint8 mem_pos);



Std_ReturnType int_to_string(uint32 data,uint8 *str);
Std_ReturnType short_to_string(uint16 data,uint8 *str);
Std_ReturnType byte_to_string(uint8 data,uint8 *str);



#endif	/* LCD_H */

