
#include"main.h"
#include "MCAL/GPIO/gpio.h"
#include "ECU/LED/led.h"
#include "ECU/KEYPAD/keypad.h"
#include "ECU/RELAY/relay.h"
#include "ECU/7_SEGMENT/_7_segment.h"
#include "ECU/DC_motor/dc_motor.h"
#include "ECU/LCD/lcd.h"

lcd_8_bit_mode lcd_1={
  .rs.pin=PIN0,.rs.port=PORTC_INDEX,.rs.direction=OUTPUT,.rs.state=LOW,  
  .en.pin=PIN1,.en.port=PORTC_INDEX,.en.direction=OUTPUT,.en.state=LOW, 
  ._8_bit[0].pin=PIN2,._8_bit[0].port=PORTC_INDEX,._8_bit[0].state=LOW,._8_bit[0].direction=OUTPUT,
  ._8_bit[1].pin=PIN3,._8_bit[1].port=PORTC_INDEX,._8_bit[1].state=LOW,._8_bit[1].direction=OUTPUT,
  ._8_bit[2].pin=PIN4,._8_bit[2].port=PORTC_INDEX,._8_bit[2].state=LOW,._8_bit[2].direction=OUTPUT,
  ._8_bit[3].pin=PIN5,._8_bit[3].port=PORTC_INDEX,._8_bit[3].state=LOW,._8_bit[3].direction=OUTPUT,
  ._8_bit[4].pin=PIN6,._8_bit[4].port=PORTC_INDEX,._8_bit[4].state=LOW,._8_bit[4].direction=OUTPUT,
  ._8_bit[5].pin=PIN7,._8_bit[5].port=PORTC_INDEX,._8_bit[5].state=LOW,._8_bit[5].direction=OUTPUT,
  ._8_bit[6].pin=PIN0,._8_bit[6].port=PORTD_INDEX,._8_bit[6].state=LOW,._8_bit[6].direction=OUTPUT,
  ._8_bit[7].pin=PIN1,._8_bit[7].port=PORTD_INDEX,._8_bit[7].state=LOW,._8_bit[7].direction=OUTPUT,
  
};
uint8 customChar[] = {
  0B11111,
  0B00001,
  0B00010,
  0B00100,
  0B01000,
  0B00100,
  0B00010,
  0B11111
};
Std_ReturnType ret=OK;

int main()
{
    ret=lcd_8_bit_init(&lcd_1);
    ret=display_string_at_position_8(&lcd_1,1,3,"MOHAMED");
    while(1)
    {
        
    }
    return 0;
}
