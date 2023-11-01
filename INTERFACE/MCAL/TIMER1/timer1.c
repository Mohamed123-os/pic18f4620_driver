#include"timer1.h"
#if TIMER1_INTERRUPT_ENABLE==1
static void (*timer1_interrupt_hndle)(void)=NULL;
#endif
static uint16 timer1_preload=0;

/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer1_Init(const timer1_config *timer)
{
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
       DISABLE_TIMER1();                                  //disable timer1
      //select register size
       switch(timer->timer1_register_size)
       {
           case TIMER18_BIT: TIMER1_8_BIT() ; break;
           case TIMER116_BIT: TIMER1_16_BIT() ; break;
           default: TIMER1_16_BIT();  break;
       }
        //select timer1 mode counter or timer and select if synchronous or not
       switch(timer->timer1_mode)
       {
           case TIMER1_TIMER_MODE: TIMER_1_TIMER_MODE(); break;
           case TIMER1_COUNTER_MODE:
                    TIMER_1_COUNTER_MODE();
                    if(timer->timer1_counter_synchronize==SYNCHRONIZE_EXTERNAL_CLOCK)
                    {
                        TIMER1_COUNTER_SYNCHRONIZE()  ;
                    }
                    else if(timer->timer1_counter_synchronize==NOT_SYNCHRONIZE_EXTERNAL_CLOCK )
                    {
                        TIMER1_COUNTER_NOT_SYNCHRONIZE() ;
                    }
           break;
       }
       
       //set  prescaler value 
       T1CONbits.T1CKPS=timer->prescaler_value;
       
        //load preloaded value
        TMR1H = (timer->timer1_preload_value) >> 8;
        TMR1L = (uint8)(timer->timer1_preload_value);
        timer1_preload = timer->timer1_preload_value;
               //select interrupt and priority features
#if TIMER1_INTERRUPT_ENABLE==1   
        TIMER1_InterruptEnable();
        TIMER1_InterruptFlagClear() ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE ==1
        Priority_levels_enable();
        if(timer->TIMER1_priority==HIGH_PRIORITY)
        {
            Priorit_high_enable() ;
            TIMER1_HighPrioritySet()  ;
            
        }
        else if(timer->TIMER1_priority==LOW_PRIORITY)
        {
            Priorit_low_enable() ;
            TIMER1_LowPrioritySet();
            
        }
#else
    
        Global_interrupt_enable();
        pripherals_interrupt_enable();
#endif
        timer1_interrupt_hndle=timer->timer1_interrupt_handler;
#endif
        
         ENABLE_TIMER1();                   //ENABEL TIMER0
    }
    
    return ret;
}
/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer1_DeInit(const timer1_config *timer)
{
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        DISABLE_TIMER1();            //disable timer1
    }
    return ret;
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer1_Write_Value(const timer1_config *timer, uint16 value)
{
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        TMR1H = (value) >> 8;
        TMR1L = (uint8)(value);
        
    }
    return ret;
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer1_Read_Value(const timer1_config *timer, uint16 *value)
{
    uint8 tmr1l,tmr1h;
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        tmr1l = TMR1L;
        tmr1h = TMR1H;
        *value = (uint16)((tmr1h << 8) + tmr1l);
    }
    return ret;
}

#if TIMER1_INTERRUPT_ENABLE==1
void TMR1_ISR(void){
    TIMER1_InterruptFlagClear();     /* Clear the interrupt flag */
    TMR1H = (timer1_preload) >> 8;   /* Initialize the pre-loaded value again */
    TMR1L = (uint8)(timer1_preload); /* Initialize the pre-loaded value again */
    if(timer1_interrupt_hndle){
        timer1_interrupt_hndle();     /* Call the callback function */
    }
}
#endif

