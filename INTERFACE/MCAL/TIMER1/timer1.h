/* 
 * File:   timer1.h
 * Author: mohamed
 *
 * Created on September 8, 2023, 8:55 PM
 */

#ifndef TIMER1_H
#define	TIMER1_H

/***************************includes section****************************************/
#include "../GPIO/gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h" 
/***************************macros sections*****************************************/
#define TIMER1_ON                            1
#define TIMER1_OFF                           0
#define TIMER18_BIT                         1
#define TIMER116_BIT                        0
#define TIMER1_TIMER_MODE                    0
#define TIMER1_COUNTER_MODE                  1
#define SYNCHRONIZE_EXTERNAL_CLOCK           1
#define NOT_SYNCHRONIZE_EXTERNAL_CLOCK       0
#define TIMER1_OSCILLATOR_ON                 1
#define TIMER1_OSCILLATOR_OFF                0
#define TIMER1_OSCILLATOR_INTERNAL_CLOCK      1
#define TIMER1_OSCILLATOR_EXTERNAL_CLOCK     0

/***************************function like macro section*****************************/
#define ENABLE_TIMER1()                T1CONbits.TMR1ON=1
#define DISABLE_TIMER1()               T1CONbits.TMR1ON=0

#define TIMER1_8_BIT()                  T1CONbits.RD16=1
#define TIMER1_16_BIT()                 T1CONbits.RD16=0

#define TIMER_1_TIMER_MODE()           T1CONbits.TMR1CS=0
#define TIMER_1_COUNTER_MODE()         T1CONbits.TMR1CS=1

#define TIMER1_OSCILLATOR_ENABLE()     T1CONbits.T1OSCEN=1
#define TIMER1_OSCILATOR_DISABLE()     T1CONbits.T1OSCEN=0

#define TIMER1_COUNTER_NOT_SYNCHRONIZE()   T1CONbits.T1SYNC=1
#define TIMER1_COUNTER_SYNCHRONIZE()       T1CONbits.T1SYNC=0

/***************************data types section**************************************/
typedef enum{
    prescaler_1=0,
    prescaler_2,
    prescaler_4,
    prescaler_8,             
}prescaler_t1;

typedef struct{
#if TIMER1_INTERRUPT_ENABLE==1
    void(*timer1_interrupt_handler)(void);
#endif
    prescaler_t1 prescaler_value;
    uint16 timer1_preload_value;
    uint8 timer1_mode ;
    uint8 timer1_register_size ;
    prioirty TIMER1_priority;
    uint8 timer1_osc_cfg ; 
    uint8 timer1_counter_synchronize; 
}timer1_config; 

/***************************software interfaces section*****************************/
Std_ReturnType Timer1_Init(const timer1_config *timer);
Std_ReturnType Timer1_DeInit(const timer1_config *timer);
Std_ReturnType Timer1_Write_Value(const timer1_config *timer, uint16 value);
Std_ReturnType Timer1_Read_Value(const timer1_config *_timer, uint16 *value);

#endif	/* TIMER1_H */

