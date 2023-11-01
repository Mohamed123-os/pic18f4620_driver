/* 
 * File:   pwm.h
 * Author: mohamed
 *
 * Created on September 22, 2023, 1:21 AM
 */

#ifndef PWM_H
#define	PWM_H

/***************************includes section****************************************/
#include "../GPIO/gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
/***************************macros sections*****************************************/
#define    PWM_ON       0X01
#define    PWM_OFF      0X00
#define    PWM_MODE     0x0F


/***************************function like macro section*****************************/
/***************************data types section**************************************/
typedef enum{
    Prescaler_is_1, 
    Prescaler_is_4, 
    Prescaler_is_16
}prescaler;

typedef enum{
    Postscaler_by_1,
    Postscaler_by_2,
    Postscaler_by_3,
    Postscaler_by_4,
    Postscaler_by_5,
    Postscaler_by_6,
    Postscaler_by_7,
    Postscaler_by_8,
    Postscaler_by_9,
    Postscaler_by_10,
    Postscaler_by_11,
    Postscaler_by_12,
    Postscaler_by_13,
    Postscaler_by_14,
    Postscaler_by_15,
    Postscaler_by_16,       
            
}postscaler;

typedef enum {
    CCP1_pwm,
    CCP2_pwm
}ccp_inst ;
typedef struct {
    pin_config pin;
    prescaler prescaler_config;
    postscaler postscaler_config;
    uint32 PWM_Frequency;  
    ccp_inst CCP_S;
    uint8 dutyCycle;
#if PWM_MODE_INTERRUPT_ENABLE_ccp1==1      
    void(*interrupt_pwm_handle_ccp1)(void);
    prioirty pwm_priority_ccp1;
#endif
#if PWM_MODE_INTERRUPT_ENABLE_ccp2==1      
    void(*interrupt_pwm_handle_ccp2)(void);
    prioirty pwm_priority_ccp2;
#endif
}pwm_t;
/***************************software interfaces section*****************************/
Std_ReturnType CCP_PWM_init(const pwm_t *configs);
Std_ReturnType CCP_PWM_Set_Duty(const pwm_t *configs, const uint8 _duty);
Std_ReturnType CCP_PWM_Start(const pwm_t *configs);
Std_ReturnType CCP_PWM_Stop(const pwm_t *configs);

#endif	/* PWM_H */

