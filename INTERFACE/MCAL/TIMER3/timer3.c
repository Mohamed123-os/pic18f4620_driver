#include"timer3.h"
#if TIMER3_INTERRUPT_ENABLE==1
static void (*timer3_interrupt_hndle)(void)=NULL;
#endif
static uint16 timer3_preload=0;

/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer3_Init(const timer3_config *timer)
{
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
       DISABLE_TIMER3();                                  //disable timer3
      //select register size
       switch(timer->timer3_register_size)
       {
           case TIMER3_8_BIT: TIMER_3_8_BIT() ; break;
           case TIMER3_16_BIT: TIMER_3_16_BIT()  ; break;
           default: TIMER_3_16_BIT() ;  break;
       }
        //select timer3 mode counter or timer and select if synchronous or not
       switch(timer->timer3_mode)
       {
           case TIMER3_TIMER_MODE: TIMER_3_TIMER_MODE(); break;
           case TIMER3_COUNTER_MODE:
                    TIMER_3_COUNTER_MODE();
                    if(timer->timer3_counter_synchronize==SYNCHRONIZE_EXTERNAL_CLOCK)
                    {
                        TIMER3_COUNTER_SYNCHRONIZE()  ;
                    }
                    else if(timer->timer3_counter_synchronize==NOT_SYNCHRONIZE_EXTERNAL_CLOCK )
                    {
                        TIMER3_COUNTER_NOT_SYNCHRONIZE() ;
                    }
           break;
       }
       
       //set  prescaler value 
       T3CONbits.T3CKPS=timer->prescaler_value;
       
        //load preloaded value
        TMR3H = (timer->timer3_preload_value) >> 8;
        TMR3L = (uint8)(timer->timer3_preload_value);
        timer3_preload = timer->timer3_preload_value;
               //select interrupt and priority features
#if TIMER3_INTERRUPT_ENABLE==1   
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear() ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE ==1
        Priority_levels_enable();
        if(timer->TIMER3_priority==HIGH_PRIORITY)
        {
            Priorit_high_enable() ;
            TIMER3_HighPrioritySet()  ;
            
        }
        else if(timer->TIMER3_priority==LOW_PRIORITY)
        {
            Priorit_low_enable() ;
            TIMER3_LowPrioritySet();
            
        }
#else
    
        Global_interrupt_enable();
        pripherals_interrupt_enable();
#endif
        timer3_interrupt_hndle=timer->timer3_interrupt_handler;
#endif
        
         ENABLE_TIMER3();                   //ENABEL TIMER3
    }
    
    return ret;
}
/**
 * 
 * @param timer
 * @return 
 */
Std_ReturnType Timer3_DeInit(const timer3_config *timer)
{
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        DISABLE_TIMER3();            //disable timer3
    }
    return ret;
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer3_Write_Value(const timer3_config *timer, uint16 value)
{
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        TMR3H = (value) >> 8;
        TMR3L = (uint8)(value);
        
    }
    return ret;
}
/**
 * 
 * @param timer
 * @param value
 * @return 
 */
Std_ReturnType Timer3_Read_Value(const timer3_config *timer, uint16 *value)
{
    uint8 tmr3l,tmr3h;
    Std_ReturnType ret=OK;
    if(timer==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        tmr3l = TMR3L;
        tmr3h = TMR3H;
        *value = (uint16)((tmr3h << 8) + tmr3l);
    }
    return ret;
}


#if TIMER3_INTERRUPT_ENABLE==1
void TMR3_ISR(void){
    TIMER3_InterruptFlagClear();     /* Clear the interrupt flag */
    TMR3H = (timer3_preload) >> 8;   /* Initialize the pre-loaded value again */
    TMR3L = (uint8)(timer3_preload); /* Initialize the pre-loaded value again */
    if(timer3_interrupt_hndle){
        timer3_interrupt_hndle();     /* Call the callback function */
    }
}
#endif


