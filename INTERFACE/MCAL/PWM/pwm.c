#include"pwm.h"

#if PWM_MODE_INTERRUPT_ENABLE_ccp1==1
static void(*PWM_handler_ccp1)(void)=NULL;
#endif
#if PWM_MODE_INTERRUPT_ENABLE_ccp2==1
static void(*PWM_handler_ccp2)(void)=NULL;
#endif


static Std_ReturnType pwm_config(const pwm_t *configs );
/**
 * 
 * @param configs
 * @return 
 */
Std_ReturnType CCP_PWM_init(const pwm_t *configs)
{
    Std_ReturnType ret=OK;
    if(NULL==configs)
    {
        ret=NOT_OK;
    }
    else
    {
        T2CONbits.TMR2ON=1;   
        pwm_config(configs);
#if PWM_MODE_INTERRUPT_ENABLE_ccp1==1
      Priority_levels_enable()  ;
      CCP1_InterruptEnable() ;
      CCP1_InterruptFlagClear() ;  
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==1
        if(configs->pwm_priority_ccp1==HIGH_PRIORITY)
        {
            Priorit_high_enable() ;
            CCP1_HighPrioritySet()  ;
        }
        else if(configs->pwm_priority_ccp1==LOW_PRIORITY)
        {
            Priorit_low_enable() ;
            CCP1_LowPrioritySet()  ;
        }
#else
        Global_interrupt_enable();
        pripherals_interrupt_enable();
#endif
        PWM_handler_ccp2=configs->interrupt_pwm_handle_ccp1;
#endif
        
#if PWM_MODE_INTERRUPT_ENABLE_ccp2==1
        Priority_levels_enable()  ;
        CCP2_InterruptEnable() ;
        CCP2_InterruptFlagClear() ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==1
        if(configs->pwm_priority_ccp2==HIGH_PRIORITY)
        {
            Priorit_high_enable() ;
            CCP2_HighPrioritySet()  ;
        }
        else if(configs->pwm_priority_ccp2==LOW_PRIORITY)
        {
            Priorit_low_enable() ;
            CCP2_LowPrioritySet()  ;
        }
#else
        Global_interrupt_enable();
        pripherals_interrupt_enable();
#endif
        PWM_handler_ccp2=configs->interrupt_pwm_handle_ccp2;
#endif
         
    }
    return ret;
    
}
/**
 * 
 * @param _ccp_obj
 * @param _duty
 * @return 
 */
Std_ReturnType CCP_PWM_Set_Duty(const pwm_t *configs, const uint8 _duty)
{
    Std_ReturnType ret=OK;
    uint16 l_duty_temp = 0;
    if(NULL==configs)
    {
        ret=NOT_OK;
    }
    else
    {
        l_duty_temp = (uint16)((float)4 * ((float)PR2 + 1.0) * ((float)_duty / 100.0));
        
        if(CCP1_pwm == configs->CCP_S){
            CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
            CCPR1L = (uint8)(l_duty_temp >> 2);
        }
        else  if(CCP2_pwm == configs->CCP_S){
            CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
            CCPR2L = (uint8)(l_duty_temp >> 2);
        }
    }
    return ret;
}
/**
 * 
 * @param _ccp_obj
 * @return 
 */
Std_ReturnType CCP_PWM_Start(const pwm_t *configs)
{
    Std_ReturnType ret=OK;
    if(NULL==configs)
    {
        ret=NOT_OK;
    }
    else
    {
         if(CCP1_pwm == configs->CCP_S){
            CCP1CONbits.CCP1M = PWM_MODE;
        }
        else if(CCP2_pwm == configs->CCP_S){
            CCP2CONbits.CCP2M = PWM_MODE;
        }
    }
    return ret;
}
/**
 * 
 * @param _ccp_obj
 * @return 
 */
Std_ReturnType CCP_PWM_Stop(const pwm_t *configs)
{
    Std_ReturnType ret=OK;
    if(NULL==configs)
    {
        ret=NOT_OK;
    }
    else
    {
         if(CCP1_pwm == configs->CCP_S){
            CCP1CONbits.CCP1M = PWM_OFF;
        }
        else if(CCP2_pwm == configs->CCP_S){
            CCP2CONbits.CCP2M = PWM_OFF;
        
        }
    }
    return ret;
    
}
/**
 * 
 * @param configs
 */
static Std_ReturnType pwm_config(const pwm_t *configs )

{
    Std_ReturnType ret=OK;
    if(NULL==configs)
    {
        ret=NOT_OK;
    }
    else
    {
    
        PR2 = (uint8)(((float)_XTAL_FREQ / ((float)configs->PWM_Frequency * 4.0 * (float)configs->prescaler_config * 
                         (float)configs->postscaler_config)) - 1);

        if(CCP1_pwm==configs->CCP_S)   CCP1CONbits.CCP1M=PWM_MODE;
        else if(CCP2_pwm==configs->CCP_S)   CCP2CONbits.CCP2M=PWM_MODE;
    }
    return ret;
}



 void PWM_ISR(void)
 {
#if PWM_MODE_INTERRUPT_ENABLE_ccp1==1
       CCP1_InterruptFlagClear() ;
       if(PWM_handler_ccp1)PWM_handler_ccp1();
#endif  
#if PWM_MODE_INTERRUPT_ENABLE_ccp2==1
       CCP2_InterruptFlagClear() ;
       if(PWM_handler_ccp2)PWM_handler_ccp2();
#endif  
 }