/* 
 * File:   timer3.h
 * Author: mohamed
 *
 * Created on September 9, 2023, 8:20 PM
 */

#ifndef TIMER3_H
#define	TIMER3_H


/***************************includes section****************************************/
#include "../GPIO/gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h" 
/***************************macros sections*****************************************/
#define TIMER3_ON                            1
#define TIMER3_OFF                           0
#define TIMER3_8_BIT                         1
#define TIMER3_16_BIT                        0
#define TIMER3_TIMER_MODE                    0
#define TIMER3_COUNTER_MODE                  1
#define SYNCHRONIZE_EXTERNAL_CLOCK           1
#define NOT_SYNCHRONIZE_EXTERNAL_CLOCK       0
#define TIMER3_OSCILLATOR_INTERNAL_CLOCK     1
#define TIMER3_OSCILLATOR_EXTERNAL_CLOCK     0

/***************************function like macro section*****************************/
#define ENABLE_TIMER3()                T3CONbits.TMR3ON=1
#define DISABLE_TIMER3()               T3CONbits.TMR3ON=0

#define TIMER_3_8_BIT()                  T3CONbits.RD16=1
#define TIMER_3_16_BIT()                 T3CONbits.RD16=0

#define TIMER_3_TIMER_MODE()           T3CONbits.TMR3CS=0
#define TIMER_3_COUNTER_MODE()         T3CONbits.TMR3CS=1

#define TIMER3_COUNTER_NOT_SYNCHRONIZE()   T3CONbits.T3SYNC=1
#define TIMER3_COUNTER_SYNCHRONIZE()       T3CONbits.T3SYNC=0

/***************************data types section**************************************/
typedef enum{
    prescaler_timer3_1=0,
    prescaler_timer3_2,
    prescaler_timer3_4,
    prescaler_timer3_8,             
}prescaler_t3;

typedef struct{
#if TIMER3_INTERRUPT_ENABLE==1
    void(*timer3_interrupt_handler)(void);
#endif
    prescaler_t3 prescaler_value;
    uint16 timer3_preload_value;
    uint8 timer3_mode ;
    uint8 timer3_register_size ;
    prioirty TIMER3_priority;
    uint8 timer3_osc_cfg ; 
    uint8 timer3_counter_synchronize; 
}timer3_config; 

/***************************software interfaces section*****************************/
Std_ReturnType Timer3_Init(const timer3_config *timer);
Std_ReturnType Timer3_DeInit(const timer3_config *timer);
Std_ReturnType Timer3_Write_Value(const timer3_config *timer, uint16 value);
Std_ReturnType Timer3_Read_Value(const timer3_config *_timer, uint16 *value);

#endif	/* TIMER3_H */

