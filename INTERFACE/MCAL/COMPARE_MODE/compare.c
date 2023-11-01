#include"compare.h"



#if COMPARE_MODE_INTERRUPT_ENABLE_ccp1==1
static void(*comparing_handler_ccp1)(void)=NULL;
#endif
#if COMPARE_MODE_INTERRUPT_ENABLE_ccp2==1
static void(*comparing_handler_ccp2)(void)=NULL;
#endif
/**
 * 
 * @param configs
 * @return 
 */
Std_ReturnType compare_init(const compare_configs *configs )
{
    Std_ReturnType ret=OK;
    if(configs==NULL)
    {
        ret=NOT_OK;
    }  
    else
    {
        if(configs->timer==timer1)
        {
            switch(configs->edge_and_mode)
            {
                case CCPX_PIN_LOW:   CCP1CONbits.CCP1M=CCPX_PIN_LOW; break;
                case CCPX_PIN_HIGH:  CCP1CONbits.CCP1M=CCPX_PIN_HIGH;break;
                case INTERRUPT_MATCH: CCP1CONbits.CCP1M=INTERRUPT_MATCH;break;
                case CCP_GEN_EVENT:   CCP1CONbits.CCP1M=CCP_GEN_EVENT;break;
                case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:CCP1CONbits.CCP1M=CCP_COMPARE_MODE_TOGGLE_ON_MATCH;break;
            }
        }
        else if(configs->timer==timer3)
        {
            switch(configs->edge_and_mode)
            {
                case CCPX_PIN_LOW:   CCP2CONbits.CCP2M=CCPX_PIN_LOW; break;
                case CCPX_PIN_HIGH:  CCP2CONbits.CCP2M=CCPX_PIN_HIGH;break;
                case INTERRUPT_MATCH: CCP2CONbits.CCP2M=INTERRUPT_MATCH;break;
                case CCP_GEN_EVENT:   CCP2CONbits.CCP2M=CCP_GEN_EVENT;break;
                case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:CCP2CONbits.CCP2M=CCP_COMPARE_MODE_TOGGLE_ON_MATCH;break;
            }
        }
        T3CONbits.T3CKPS=configs->mode_conf;
        pin_directoin_intialize(&configs->pin);
        
#if COMPARE_MODE_INTERRUPT_ENABLE_ccp1==1
      Priority_levels_enable()  ;
      CCP1_InterruptEnable() ;
      CCP1_InterruptFlagClear() ;  
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==1
        if(configs->compare_priority_ccp1==HIGH_PRIORITY)
        {
            Priorit_high_enable() ;
            CCP1_HighPrioritySet()  ;
        }
        else if(configs->compare_priority_ccp1==LOW_PRIORITY)
        {
            Priorit_low_enable() ;
            CCP1_LowPrioritySet()  ;
        }
#else
        Global_interrupt_enable();
        pripherals_interrupt_enable();
#endif
        comparing_handler_ccp1=configs->interrupt_compare_handle_ccp1;
#endif
        
#if COMPARE_MODE_INTERRUPT_ENABLE_ccp2==1
        Priority_levels_enable()  ;
        CCP2_InterruptEnable() ;
        CCP2_InterruptFlagClear() ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==1
        if(configs->compare_priority_ccp2==HIGH_PRIORITY)
        {
            Priorit_high_enable() ;
            CCP2_HighPrioritySet()  ;
        }
        else if(configs->compare_priority_ccp2==LOW_PRIORITY)
        {
            Priorit_low_enable() ;
            CCP2_LowPrioritySet()  ;
        }
#else
        Global_interrupt_enable();
        pripherals_interrupt_enable();
#endif
        comparing_handler_ccp2=configs->interrupt_compare_handle_ccp2;
#endif
             
    }
    return ret;
}
/**
 * 
 * @param configs
 * @return 
 */
Std_ReturnType compare_deinit(const compare_configs *configs )
{
   Std_ReturnType ret=OK;
    if(configs==NULL)
    {
        ret=NOT_OK;
    }  
    else
    {
        
    }
    return ret; 
}
/**
 * 
 * @param _compare_status
 * @return 
 */
Std_ReturnType CCP_IsCompareComplete(uint8 *_compare_status)
{
    Std_ReturnType ret=OK;
    if(_compare_status==NULL)
    {
        ret=NOT_OK;
    }  
    else
    {
        if(COMPARE_READY == PIR1bits.CCP1IF){
            *_compare_status = COMPARE_READY;
            CCP1_InterruptFlagClear();
        }
        else{
            *_compare_status = COMPARE_NOT_READY;
        }
    }
    return ret;
}
/**
 * 
 * @param ccp_obj
 * @param compare_value
 * @return 
 */
Std_ReturnType CCP_Compare_Mode_Set_Value(const compare_configs *ccp_obj, uint16 compare_value)
{
    Std_ReturnType ret=OK;
    CCP_REG_T capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
    if(ccp_obj==NULL)
    {
        ret=NOT_OK;
    }  
    else
    {
        /* Copy compared value */
        capture_temp_value.ccpr_16Bit = compare_value;

        if(timer1 == ccp_obj->timer){
            CCPR1L = capture_temp_value.ccpr_low;
            CCPR1H = capture_temp_value.ccpr_high;
        }
        else if(timer3 == ccp_obj->timer){
            CCPR2L = capture_temp_value.ccpr_low;
            CCPR2H = capture_temp_value.ccpr_high;
        }
        else{ /* Nothing */ }
        
        ret = OK;
    }
    
   
    return ret;
}


 void COMOPARE_ISR(void)
    {
#if COMPARE_MODE_INTERRUPT_ENABLE_ccp1==1
       CCP1_InterruptFlagClear() ;
       if(comparing_handler_ccp1)comparing_handler_ccp1();
#endif  
#if COMPARE_MODE_INTERRUPT_ENABLE_ccp2==1
       CCP2_InterruptFlagClear() ;
       if(comparing_handler_ccp2)comparing_handler_ccp2();
#endif  
    }