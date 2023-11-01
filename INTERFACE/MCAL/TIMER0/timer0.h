/* 
 * File:   timer0.h
 * Author: mohamed
 *
 * Created on September 8, 2023, 1:30 AM
 */

#ifndef TIMER0_H
#define	TIMER0_H

/***************************includes section****************************************/
#include "../GPIO/gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h" 
/***************************macros sections*****************************************/
#define TIMER0_ON             1
#define TIMER0_OFF            0
#define TIMER0_8_BIT          1
#define TIMER0_16_BIT         0
#define RISING_EDGE           1
#define FALLING_EDGE          0
#define TIMER0_TIMER_MODE     0
#define TIMER0_COUNTER_MODE   1
#define PRESCALER_ON          1
#define PRESCALER_OFF         0

/***************************function like macro section*****************************/
#define ENABLE_TIMER0()                T0CONbits.TMR0ON=1
#define DISABLE_TIMER0()               T0CONbits.TMR0ON=0
#define TIMER_8_BIT()                  T0CONbits.T08BIT=1
#define TIMER_16_BIT()                 T0CONbits.T08BIT=0
#define TIMER_0_RISING_EDGE()          T0CONbits.T0SE=1
#define TIMER_0_FALLING_EDGE()         T0CONbits.T0SE=0
#define TIMER_0_TIMER_MODE()           T0CONbits.T0CS=0
#define TIMER_0_COUNTER_MODE()         T0CONbits.T0CS=1
#define TIMER_0_ENABLE_PRESCALER()     T0CONbits.PSA=0
#define TIMER_0_DISABLE_PRESCALER()    T0CONbits.PSA=1
/***************************data types section**************************************/
typedef enum{
    prescaler_by_2=0,
    prescaler_by_4,
    prescaler_by_8,
    prescaler_by_16,        
    prescaler_by_32,
    prescaler_by_64,
    prescaler_by_128,
    prescaler_by_256       
}prescaler;

typedef struct
{
#if TIMER0_INTERRUPT_ENABLE==1
    void(*timer0_interrupt_handler)(void);
#endif
    prescaler prescaler_value;
    uint16 timer0_preload_value;
    uint8 prescaler_enable ;
    uint8 timer0_counter_edge ;
    uint8 timer0_mode ;
    uint8 timer0_register_size ;
    prioirty TIMER0_priority;
    
}timer0_t;
/***************************software interfaces section*****************************/
Std_ReturnType Timer0_Init(const timer0_t *timer);
Std_ReturnType Timer0_DeInit(const timer0_t *timer);
Std_ReturnType Timer0_Write_Value(const timer0_t *timer, uint16 value);
Std_ReturnType Timer0_Read_Value(const timer0_t *timer, uint16 *value);

#endif	/* TIMER0_H */

