#include"timer2.h"
#if TIMER2_INTERRUPT_ENABLE==1
static void (*timer2_interrupt_hndle)(void)=NULL;
#endif
static uint8 timer2_preload=0;


/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer2_Init(const timer2_config *timer)
{
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        T2CONbits.TMR2ON=0;       //disable timer2 
        T2CONbits.T2CKPS=timer->prescaler_value; //select prescaler
        T2CONbits.TOUTPS=timer->postscaler_value; //select postscaler value
        TMR2 = timer->timer2_preload_value;
        timer2_preload = timer->timer2_preload_value;
        
#if TIMER2_INTERRUPT_ENABLE==1   
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear() ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE ==1
        Priority_levels_enable();
        if(timer->timer2_priority==HIGH_PRIORITY)
        {
            Priorit_high_enable() ;
            TIMER2_HighPrioritySet()  ;
            
        }
        else if(timer->timer2_priority==LOW_PRIORITY)
        {
            Priorit_low_enable() ;
            TIMER2_LowPrioritySet();
            
        }
#else
    
        Global_interrupt_enable();
        pripherals_interrupt_enable();
#endif
        timer2_interrupt_hndle=timer->timer2_interrupt_handler;
#endif

        T2CONbits.TMR2ON=1;       //enable timer2 
    }
    return ret;
}
/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer2_DeInit(const timer2_config *timer)
{
   Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        T2CONbits.TMR2ON=1;       //enable timer2 
    }
    return ret; 
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer2_Write_Value(const timer2_config *timer, uint8 value)
{
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        TMR2=value;
    }
    return ret;
}
/**
 * 
 * @param _timer
 * @param value
 * @return 
 */
Std_ReturnType Timer2_Read_Value(const timer2_config *timer, uint8 *value)
{
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        *value=TMR2;
    }
    return ret;
}

#if TIMER2_INTERRUPT_ENABLE==1
void TMR2_ISR(void){
    TIMER2_InterruptFlagClear();     /* Clear the interrupt flag */
    TMR2= timer2_preload;  /* Initialize the pre-loaded value again */
    if(timer2_interrupt_hndle)
    {
        timer2_interrupt_hndle();     /* Call the callback function */
    }
}
#endif

