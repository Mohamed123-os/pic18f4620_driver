/* 
 * File:   interrupt_generation.h
 * Author: mohamed
 *
 * Created on August 27, 2023, 12:12 PM
 */

#ifndef INTERRUPT_GENERATION_H
#define	INTERRUPT_GENERATION_H
/***************************includes section****************************************/
/***************************macros sections*****************************************/
#define INTERRUPT_GENERATE                   1
#define INTERRUPT_PRIORITY_LEVELS_ENABLE     INTERRUPT_GENERATE
#define INTERRUPT_INTx_ENABLE                INTERRUPT_GENERATE
#define INTERRUPT_CHANGE_ENABLE              INTERRUPT_GENERATE
#define ADC_INTERRUPT_ENABLE                 INTERRUPT_GENERATE
#define TIMER0_INTERRUPT_ENABLE              INTERRUPT_GENERATE
#define TIMER1_INTERRUPT_ENABLE              INTERRUPT_GENERATE
#define TIMER2_INTERRUPT_ENABLE              INTERRUPT_GENERATE
#define TIMER3_INTERRUPT_ENABLE              INTERRUPT_GENERATE
#define CCP1_INTERRUPT_FEATURE_ENABLE        INTERRUPT_GENERATE
#define CCP2_INTERRUPT_FEATURE_ENABLE        INTERRUPT_GENERATE
#define COMPARE_MODE_INTERRUPT_ENABLE_ccp1   INTERRUPT_GENERATE
#define COMPARE_MODE_INTERRUPT_ENABLE_ccp2   INTERRUPT_GENERATE
#define PWM_MODE_INTERRUPT_ENABLE_ccp1       INTERRUPT_GENERATE
#define PWM_MODE_INTERRUPT_ENABLE_ccp2       INTERRUPT_GENERATE
//#define TX_INTERRPT_ENABLE                   INTERRUPT_GENERATE
//#define RX_INTERRPT_ENABLE                   INTERRUPT_GENERATE
/***************************function like macro section*****************************/
/***************************data types section**************************************/
/***************************software interfaces section*****************************/

#endif	/* INTERRUPT_GENERATION_H */


