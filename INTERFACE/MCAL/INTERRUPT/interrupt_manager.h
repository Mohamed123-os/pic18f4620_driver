/* 
 * File:   interrupt_manager.h
 * Author: mohamed
 *
 * Created on August 27, 2023, 12:11 PM
 */

#ifndef INTERRUPT_MANAGER_H
#define	INTERRUPT_MANAGER_H


/***************************includes section****************************************/
#include"interrupt_config.h"
/***************************macros sections*****************************************/
/***************************function like macro section*****************************/
/***************************data types section**************************************/
/***************************software interfaces section*****************************/
void INT_0_ISR(void);
void INT_1_ISR(void);
void INT_2_ISR(void);
void RB4__ISR(void);
void RB5__ISR(void);
void RB6__ISR(void);
void RB7__ISR(void);
void ADC_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);
void COMOPARE_ISR(void);
void PWM_ISR(void);
void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);
#endif	/* INTERRUPT_MANAGER_H */
