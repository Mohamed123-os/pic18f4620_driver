/* 
 * File:   capture.h
 * Author: mohamed
 *
 * Created on September 11, 2023, 1:48 PM
 */

#ifndef CAPTURE_H
#define	CAPTURE_H

/***************************includes section****************************************/
#include "../GPIO/gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
/***************************macros sections*****************************************/
#define CAPTURE_DISABLE       0x00
#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE    ((uint8)0x07)

#define CCP1_CAPTURE_NOT_READY              0X00
#define CCP1_CAPTURE_READY                  0X01
/***************************function like macro section*****************************/

#define DISABLE_CCP1()                     CCP1CONbits.CCP1M=0;
#define DISABLE_CCP2()                     CCP2CONbits.CCP2M=0;

/***************************data types section**************************************/
typedef enum{
    timer1,
    timer3
}choose_timer;

typedef enum{
    CCP1_t,
    CCP2_t
}ccp_choose;

typedef union{
    struct{
        uint8 ccpr_low;  /* CCPR1 low register */
        uint8 ccpr_high; /* CCPR1 high register */
    };
    struct{
        uint16 ccpr_16Bit; /* Read CCPR1 as a 16 Bit value */
    };
}CCP_REG_T;

typedef enum{
    CCP1_CCP2_TIMER3 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER1
}ccp_capture_timer_t;

typedef struct {
    
    ccp_choose ccpx;
    ccp_capture_timer_t timer_ccp;
    pin_config pin;
    uint8 edge_and_mode ;
#if CCP1_INTERRUPT_FEATURE_ENABLE==1
    void (* CCP1_InterruptHandler)(void);   /* Call back used for all CCP1 Modes */
     prioirty CCP1_priority;   /* Configure the CCP1 mode interrupt */
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==1
    void (* CCP2_InterruptHandler)(void);   /* Call back used for all CCP2 Modes */
    prioirty CCP2_priority;   /* Configure the CCP1 mode interrupt */
#endif
}capture_t;
/***************************software interfaces section*****************************/
Std_ReturnType capture_init(const capture_t *capture);
Std_ReturnType capture_deinit(const capture_t *capture);
Std_ReturnType CCP1_IsCapturedDataReady(uint8 *_capture_status);
Std_ReturnType CCP1_Capture_Mode_Read_Value(uint16 *capture_value);
#endif	/* CAPTURE_H */

