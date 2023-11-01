/* 
 * File:   timer2.h
 * Author: mohamed
 *
 * Created on September 9, 2023, 6:15 PM
 */

#ifndef TIMER2_H
#define	TIMER2_H


/***************************includes section****************************************/
#include "../GPIO/gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h" 
/***************************macros sections*****************************************/
#define TIMER2_ON                    1
#define TIMER2_OFF                   0

/***************************function like macro section*****************************/
/***************************data types section**************************************/
typedef enum
{
    prescaler_timer2_1=0,
    prescaler_timer2_4,
    prescaler_timer2_16
}prescaler_t2;

typedef enum
{
    postscaler_1,
    postscaler_2,
    postscaler_3,
    postscaler_4,
    postscaler_5,
    postscaler_6,
    postscaler_7,
    postscaler_8,
    postscaler_9,
    postscaler_10,
    postscaler_11,
    postscaler_12,
    postscaler_13,
    postscaler_14,
    postscaler_15,
    postscaler_16,
}postscaler;

typedef struct{
#if TIMER2_INTERRUPT_ENABLE==1
    void(*timer2_interrupt_handler)(void);
#endif
    prescaler_t2 prescaler_value;
    uint16 timer2_preload_value;
    postscaler postscaler_value;
    prioirty timer2_priority;
}timer2_config; 

/***************************software interfaces section*****************************/
Std_ReturnType Timer2_Init(const timer2_config *timer);
Std_ReturnType Timer2_DeInit(const timer2_config *timer);
Std_ReturnType Timer2_Write_Value(const timer2_config *timer, uint8 value);
Std_ReturnType Timer2_Read_Value(const timer2_config *_timer, uint8 *value);

#endif	/* TIMER2_H */

