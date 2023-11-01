
#include "interrupt_manager.h"


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == 1 
void __interrupt() InterruptManagerHigh(void)
{
    //external interrupt intx
#if INTERRUPT_INTx_ENABLE==1     
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCEUR == INTCONbits.INT0IF))
    {
        INT_0_ISR();
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCEUR == INTCON3bits.INT1IE))
    {
        INT_1_ISR();
    }
    
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCEUR == INTCON3bits.INT2IF))
    {
        INT_2_ISR();
    }
   
    else{ /* Nothing */ }
#endif
    //external inteeupt on change 
#if INTERRUPT_CHANGE_ENABLE ==1
    if((INTERRUPT_ENABLE==INTCONbits.RBIE)&&(INTERRUPT_OCCEUR==INTCONbits.RBIF)&&(PORTBbits.RB4 == HIGH))
    {
        RB4__ISR();
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE)&&(INTERRUPT_OCCEUR==INTCONbits.RBIF)&&(PORTBbits.RB5 == HIGH))
    {
        RB5__ISR();
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE)&&(INTERRUPT_OCCEUR==INTCONbits.RBIF)&&(PORTBbits.RB6 == HIGH))
    {
        RB6__ISR();
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE)&&(INTERRUPT_OCCEUR==INTCONbits.RBIF)&&(PORTBbits.RB7 == HIGH))
    {
        RB7__ISR();
    }
#endif
    //internal adc interrupt 
#if ADC_INTERRUPT_ENABLE ==1
     if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCEUR == PIR1bits.ADIF)){
        ADC_ISR();
    }
#endif 
    
   //internal timer0 interrupt 
#if TIMER0_INTERRUPT_ENABLE ==1
     if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCEUR == INTCONbits.TMR0IF)){
        TMR0_ISR();
    }
#endif
    
   //internal timer1 interrupt 
#if TIMER1_INTERRUPT_ENABLE ==1
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCEUR == PIR1bits.TMR1IF)){
        TMR1_ISR();
    }
#endif
    
 //internal timer2 interrupt 
#if TIMER2_INTERRUPT_ENABLE ==1    
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCEUR == PIR1bits.TMR2IF)){
        TMR2_ISR();
    }
#endif
    
//internal timer3 interrupt 
#if TIMER3_INTERRUPT_ENABLE ==1       
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCEUR == PIR2bits.TMR3IF)){
        TMR3_ISR();
    }
#endif
    
    
 #if COMPARE_MODE_INTERRUPT_ENABLE_ccp1==1 
/* ============ CCP1 and CCP2 Modules Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCEUR == PIR1bits.CCP1IF)){
         COMOPARE_ISR();
    }
#endif
#if COMPARE_MODE_INTERRUPT_ENABLE_ccp2==1    
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCEUR == PIR2bits.CCP2IF)){
          COMOPARE_ISR();
    }
#endif
    
    
    
#if PWM_MODE_INTERRUPT_ENABLE_ccp1==1 
/* ============ CCP1 and CCP2 Modules Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCEUR == PIR1bits.CCP1IF)){
       PWM_ISR();
    }
#endif
#if PWM_MODE_INTERRUPT_ENABLE_ccp2==1    
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCEUR == PIR2bits.CCP2IF)){
          PWM_ISR();
    }
#endif 
    
    
    
#if TX_INTERRPT_ENABLE ==1
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCEUR == PIR1bits.TXIF)){
        EUSART_TX_ISR();
    }
    else{ /* Nothing */ }
#endif
#if RX_INTERRPT_ENABLE ==1
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCEUR == PIR1bits.RCIF)){
        EUSART_RX_ISR();
    }
    else{ /* Nothing */ }
#endif
    
    
    
}





/**********************************low priority section*****************************/



void __interrupt(low_priority) InterruptManagerLow(void)
{
  //external interrupt intx
#if INTERRUPT_INTx_ENABLE==1     
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCEUR == INTCONbits.INT0IF))
    {
        INT_0_ISR();
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCEUR == INTCON3bits.INT1IE))
    {
        INT_1_ISR();
    }
    
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCEUR == INTCON3bits.INT2IF))
    {
        INT_2_ISR();
    }
   
    else{ /* Nothing */ }
#endif
    //external inteeupt on change 
#if INTERRUPT_CHANGE_ENABLE ==1
    if((INTERRUPT_ENABLE==INTCONbits.RBIE)&&(INTERRUPT_OCCEUR==INTCONbits.RBIF)&&(PORTBbits.RB4 == HIGH))
    {
        RB4__ISR();
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE)&&(INTERRUPT_OCCEUR==INTCONbits.RBIF)&&(PORTBbits.RB5 == HIGH))
    {
        RB5__ISR();
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE)&&(INTERRUPT_OCCEUR==INTCONbits.RBIF)&&(PORTBbits.RB6 == HIGH))
    {
        RB6__ISR();
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE)&&(INTERRUPT_OCCEUR==INTCONbits.RBIF)&&(PORTBbits.RB7 == HIGH))
    {
        RB7__ISR();
    }
#endif
    //internal adc interrupt 
#if ADC_INTERRUPT_ENABLE ==1
     if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCEUR == PIR1bits.ADIF)){
        ADC_ISR();
    }
#endif 
    
   //internal timer0 interrupt 
#if TIMER0_INTERRUPT_ENABLE ==1
     if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCEUR == INTCONbits.TMR0IF)){
        TMR0_ISR();
    }
#endif  
     //internal timer1 interrupt 
#if TIMER1_INTERRUPT_ENABLE ==1
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCEUR == PIR1bits.TMR1IF)){
        TMR1_ISR();
    }
#endif
    
    //internal timer2 interrupt 
#if TIMER2_INTERRUPT_ENABLE ==1    
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCEUR == PIR1bits.TMR2IF)){
        TMR2_ISR();
    }
#endif
    
    //internal timer3 interrupt 
#if TIMER3_INTERRUPT_ENABLE ==1       
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCEUR == PIR2bits.TMR3IF)){
        TMR3_ISR();
    }
#endif
    
    
    
    
#if COMPARE_MODE_INTERRUPT_ENABLE_ccp1==1 
/* ============ CCP1 and CCP2 Modules Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCEUR == PIR1bits.CCP1IF)){
         COMOPARE_ISR();
    }
#endif
#if COMPARE_MODE_INTERRUPT_ENABLE_ccp2==1    
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCEUR == PIR2bits.CCP2IF)){
          COMOPARE_ISR();
    }
#endif
    
 #if PWM_MODE_INTERRUPT_ENABLE_ccp1==1 
/* ============ CCP1 and CCP2 Modules Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCEUR == PIR1bits.CCP1IF)){
       PWM_ISR();
    }
#endif
#if PWM_MODE_INTERRUPT_ENABLE_ccp2==1    
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCEUR == PIR2bits.CCP2IF)){
          PWM_ISR();
    }
#endif    
    
 #if TX_INTERRPT_ENABLE ==1
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCEUR == PIR1bits.TXIF)){
        EUSART_TX_ISR();
    }
    else{ /* Nothing */ }
#endif
#if RX_INTERRPT_ENABLE ==1
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCEUR == PIR1bits.RCIF)){
        EUSART_RX_ISR();
    }
    else{ /* Nothing */ }
#endif
    
    
}








/*********************************no priority section********************************/

#else
void __interrupt() InterruptManager(void)
{
    
//external interrupt intx
#if INTERRUPT_INTx_ENABLE==1     
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCEUR == INTCONbits.INT0IF))
    {
        INT_0_ISR();
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCEUR == INTCON3bits.INT1IE))
    {
        INT_1_ISR();
    }
    
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCEUR == INTCON3bits.INT2IF))
    {
        INT_2_ISR();
    }
   
    else{ /* Nothing */ }
#endif
    //external inteeupt on change 
#if INTERRUPT_CHANGE_ENABLE ==1
    if((INTERRUPT_ENABLE==INTCONbits.RBIE)&&(INTERRUPT_OCCEUR==INTCONbits.RBIF)&&(PORTBbits.RB4 == HIGH))
    {
        RB4__ISR();
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE)&&(INTERRUPT_OCCEUR==INTCONbits.RBIF)&&(PORTBbits.RB5 == HIGH))
    {
        RB5__ISR();
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE)&&(INTERRUPT_OCCEUR==INTCONbits.RBIF)&&(PORTBbits.RB6 == HIGH))
    {
        RB6__ISR();
    }
    if((INTERRUPT_ENABLE==INTCONbits.RBIE)&&(INTERRUPT_OCCEUR==INTCONbits.RBIF)&&(PORTBbits.RB7 == HIGH))
    {
        RB7__ISR();
    }
#endif
    //internal adc interrupt 
#if ADC_INTERRUPT_ENABLE ==1
     if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCEUR == PIR1bits.ADIF)){
        ADC_ISR();
    }
#endif 
    
   //internal timer0 interrupt 
#if TIMER0_INTERRUPT_ENABLE ==1
     if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCEUR == INTCONbits.TMR0IF)){
        TMR0_ISR();
    }
#endif  
    
     //internal timer1 interrupt 
#if TIMER1_INTERRUPT_ENABLE ==1
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCEUR == PIR1bits.TMR1IF)){
        TMR1_ISR();
    }
#endif
    
    //internal timer2 interrupt 
#if TIMER2_INTERRUPT_ENABLE ==1    
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCEUR == PIR1bits.TMR2IF)){
        TMR2_ISR();
    }
#endif
    //internal timer3 interrupt 
#if TIMER3_INTERRUPT_ENABLE ==1       
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCEUR == PIR2bits.TMR3IF)){
        TMR3_ISR();
    }
#endif
    
#if COMPARE_MODE_INTERRUPT_ENABLE_ccp1==1 
/* ============ CCP1 and CCP2 Modules Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCEUR == PIR1bits.CCP1IF)){
         COMOPARE_ISR();
    }
#endif
#if COMPARE_MODE_INTERRUPT_ENABLE_ccp2==1    
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCEUR == PIR2bits.CCP2IF)){
          COMOPARE_ISR();
    }
#endif
    
#if PWM_MODE_INTERRUPT_ENABLE_ccp1==1 
/* ============ CCP1 and CCP2 Modules Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCEUR == PIR1bits.CCP1IF)){
       PWM_ISR();
    }
#endif
#if PWM_MODE_INTERRUPT_ENABLE_ccp2==1    
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCEUR == PIR2bits.CCP2IF)){
          PWM_ISR();
    }
#endif    
   #if TX_INTERRPT_ENABLE ==1
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCEUR == PIR1bits.TXIF)){
        EUSART_TX_ISR();
    }
    else{ /* Nothing */ }
#endif
#if RX_INTERRPT_ENABLE ==1
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCEUR == PIR1bits.RCIF)){
        EUSART_RX_ISR();
    }
    else{ /* Nothing */ }
#endif
    
    
    
}
#endif