#include"timer0.h"
#if TIMER0_INTERRUPT_ENABLE==1
static void (*timer0_interrupt_hndle)(void)=NULL;
#endif
static uint16 timer0_preload=0;


/**
 * 
 * @param _timer
 * @return 
 */
Std_ReturnType Timer0_Init(const timer0_t *timer)
{
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
       DISABLE_TIMER0();                                  //disable timer0
      //select register size
       switch(timer->timer0_register_size)
       {
           case TIMER0_8_BIT: TIMER_8_BIT() ; break;
           case TIMER0_16_BIT: TIMER_16_BIT() ; break;
           default: TIMER_16_BIT();  break;
       }
       
       //select timer0 mode counter or timer
       switch(timer->timer0_mode)
       {
           case TIMER0_TIMER_MODE: TIMER_0_TIMER_MODE(); break;
           case TIMER0_COUNTER_MODE:
                        TIMER_0_COUNTER_MODE();
                        if(timer->timer0_counter_edge==RISING_EDGE )
                        {
                            TIMER_0_RISING_EDGE() ;
                        }
                        else if(timer->timer0_counter_edge==FALLING_EDGE )
                        {
                            TIMER_0_FALLING_EDGE();
                        }
                        else
                        {
                            TIMER_0_RISING_EDGE() ;
                        }
               break;
       }
       
       //select prescaler
       if(timer->prescaler_enable==PRESCALER_ON  )
       {
           TIMER_0_ENABLE_PRESCALER();   
       }
       else if(timer->prescaler_enable==PRESCALER_OFF )
       {
            TIMER_0_DISABLE_PRESCALER();
       }
         T0CONbits.T0PS=timer->prescaler_value;  //set prescaler value 
       //load preloaded value
        TMR0H = (timer->timer0_preload_value) >> 8;
        TMR0L = (uint8)(timer->timer0_preload_value);
        timer0_preload = timer->timer0_preload_value;
        
        //select interrupt and priority features
#if TIMER0_INTERRUPT_ENABLE==1   
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear() ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE ==1
        Priority_levels_enable();
        if(timer->TIMER0_priority==HIGH_PRIORITY)
        {
            Priorit_high_enable() ;
            TIMER0_HighPrioritySet()  ;
            
        }
        else if(timer->TIMER0_priority==LOW_PRIORITY)
        {
            Priorit_low_enable() ;
            TIMER0_LowPrioritySet();
            
        }
#else
    
        Global_interrupt_enable();
        pripherals_interrupt_enable();
#endif
        timer0_interrupt_hndle=timer->timer0_interrupt_handler;
#endif
        
         ENABLE_TIMER0();                   //ENABEL TIMER0
    }

    return ret;
}
/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer0_DeInit(const timer0_t *timer)
{
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        DISABLE_TIMER0();            //disable timer0
    }
    return ret;
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer0_Write_Value(const timer0_t *timer, uint16 value)
{
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        TMR0H = (value) >> 8;
        TMR0L = (uint8)(value);
        
    }
    return ret;
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer0_Read_Value(const timer0_t *timer, uint16 *value)
{
    uint8 tmr0l,tmr0h;
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        tmr0l = TMR0L;
        tmr0h = TMR0H;
        *value = (uint16)((tmr0h << 8) + tmr0l);
    }
    return ret;
}
#if TIMER0_INTERRUPT_ENABLE==1
void TMR0_ISR(void){
    TIMER0_InterruptFlagClear();     /* Clear the interrupt flag */
    TMR1H = (timer0_preload) >> 8;   /* Initialize the pre-loaded value again */
    TMR1L = (uint8)(timer0_preload); /* Initialize the pre-loaded value again */
    if(timer0_interrupt_hndle){
        timer0_interrupt_hndle();     /* Call the callback function */
    }
}
#endif