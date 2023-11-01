/* 
 * File:   compare.h
 * Author: mohamed
 *
 * Created on September 11, 2023, 7:16 PM
 */

#ifndef COMPARE_H
#define	COMPARE_H

/***************************includes section****************************************/
#include "../GPIO/gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
/***************************macros sections*****************************************/
#define COMPARE_ENABLE        0X01
#define COMPARE_DISABLE       0X00
#define COMPARE_READY         0X01
#define COMPARE_NOT_READY     0X00
#define CCPX_PIN_LOW          ((uint8)0x08)
#define CCPX_PIN_HIGH         ((uint8)0x09)
#define INTERRUPT_MATCH       ((uint8)0x0A)
#define CCP_GEN_EVENT         ((uint8)0x0B)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH   ((uint8)0x02)

/***************************function like macro section*****************************/
/***************************data types section**************************************/
typedef enum{
    timer1,
    timer3
}timer_select;

typedef enum{
    TIMER1_CCP_CLOCK_COURCE=0,
    TIMER1_CCP1_CLOCK_COURCE,
    TIMER3_CCP2_CLOCK_COURCE,
    TIMER3_CCP_CLOCK_COURCE        
}compare_mode_select_configs;

typedef union{
    struct{
        uint8 ccpr_low;  /* CCPR1 low register */
        uint8 ccpr_high; /* CCPR1 high register */
    };
    struct{
        uint16 ccpr_16Bit; /* Read CCPR1 as a 16 Bit value */
    };
}CCP_REG_T;

typedef struct{
    compare_mode_select_configs mode_conf;
    timer_select timer;
    pin_config pin;
    uint8 edge_and_mode ;
#if COMPARE_MODE_INTERRUPT_ENABLE_ccp1==1      
    void(*interrupt_compare_handle_ccp1)(void);
    prioirty compare_priority_ccp1;
#endif
#if COMPARE_MODE_INTERRUPT_ENABLE_ccp2==1      
    void(*interrupt_compare_handle_ccp2)(void);
    prioirty compare_priority_ccp2;
#endif
}compare_configs;

/***************************software interfaces section*****************************/
Std_ReturnType compare_init(const compare_configs *configs );
Std_ReturnType compare_deinit(const compare_configs *configs );
Std_ReturnType CCP_IsCompareComplete(uint8 *_compare_status);
Std_ReturnType CCP_Compare_Mode_Set_Value(const compare_configs *ccp_obj, uint16 compare_value);

#endif	/* COMPARE_H */

