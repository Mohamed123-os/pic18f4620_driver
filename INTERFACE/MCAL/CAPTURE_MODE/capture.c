#include"capture.h"

#if CCP1_INTERRUPT_FEATURE_ENABLE==1
static void(*ccp1_handler)(void)=NULL;
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==1
static void(*ccp2_handler)(void)=NULL;
#endif
/**
 * 
 * @param capture
 * @return 
 */
Std_ReturnType capture_init(const capture_t *capture)
{
    Std_ReturnType ret=OK;
    if(NULL==capture)
    {
        ret=NOT_OK;
    }
    else
    {
        DISABLE_CCP1() ;          //disable ccp1
        DISABLE_CCP1() ;          //disable ccp2
        switch(capture->ccpx)
        {
            case  CCP1_t:
                CCP1CONbits.CCP1M=capture->edge_and_mode;
                pin_directoin_intialize(&(capture->pin));
                break;
            case  CCP2_t:
                CCP2CONbits.CCP2M=capture->edge_and_mode;
                pin_directoin_intialize(&(capture->pin));
                break;
            default:
                CCP1CONbits.CCP1M=capture->edge_and_mode;
                pin_directoin_intialize(&(capture->pin));
                break;    
        }

        if(CCP1_CCP2_TIMER3 == capture->timer_ccp){
            /* Timer3 is the capture/compare clock source for the CCP modules */
            T3CONbits.T3CCP1 = 0; 
            T3CONbits.T3CCP2 = 1;
        }
        else if(CCP1_TIMER1_CCP2_TIMER3 == capture->timer_ccp){
            /* Timer3 is the capture/compare clock source for CCP2 */
            /* Timer1 is the capture/compare clock source for CCP1 */
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 0;
        }
        else if(CCP1_CCP2_TIMER1 == capture->timer_ccp){
            /* Timer1 is the capture/compare clock source for the CCP modules */
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 0;
        }
        else{ /* Nothing */ }
        
        
#if CCP1_INTERRUPT_FEATURE_ENABLE==1
        Priority_levels_enable()  ;
        CCP1_InterruptEnable() ;
        CCP1_InterruptFlagClear() ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==1
        if(capture->CCP1_priority==HIGH_PRIORITY)
        {
            Priorit_high_enable() ;
            CCP1_HighPrioritySet()  ;
        }
        else if(capture->CCP1_priority==LOW_PRIORITY)
        {
            Priorit_low_enable() ;
            CCP1_LowPrioritySet()  ;
        }
#else
        Global_interrupt_enable();
        pripherals_interrupt_enable();
#endif
        ccp1_handler=capture->CCP1_InterruptHandler;
#endif
        
        
        
        
#if CCP2_INTERRUPT_FEATURE_ENABLE==1
        Priority_levels_enable()  ;
        CCP2_InterruptEnable() ;
        CCP2_InterruptFlagClear() ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==1
        if(capture->CCP2_priority==HIGH_PRIORITY)
        {
            Priorit_high_enable() ;
            CCP2_HighPrioritySet()  ;
        }
        else if(capture->CCP2_priority==LOW_PRIORITY)
        {
            Priorit_low_enable() ;
            CCP2_LowPrioritySet()  ;
        }
#else
        Global_interrupt_enable();
        pripherals_interrupt_enable();
#endif
        ccp2_handler=capture->CCP2_InterruptHandler;
#endif
                
        
        
    }
    return ret;
}
/**
 * 
 * @param capture
 * @return 
 */
Std_ReturnType capture_deinit(const capture_t *capture)
{
    Std_ReturnType ret=OK;
    if(NULL==capture)
    {
        ret=NOT_OK;
    }
    else
    {
        DISABLE_CCP1() ;          //disable ccp1
        DISABLE_CCP1() ;          //disable ccp2
    }
    return ret;
}
/**
 * 
 * @param _capture_status
 * @return 
 */
Std_ReturnType CCP1_IsCapturedDataReady(uint8 *_capture_status)
{
    
    Std_ReturnType ret = NOT_OK;
    if(NULL == _capture_status){
        ret = NOT_OK;
    }
    else{
        if(CCP1_CAPTURE_READY == PIR1bits.CCP1IF){
            *_capture_status = CCP1_CAPTURE_READY;
            CCP1_InterruptFlagClear();
        }
        else{
            *_capture_status = CCP1_CAPTURE_NOT_READY;
        }
        ret = OK;
    }
    return ret;
}
/**
 * 
 * @param capture_value
 * @return 
 */
Std_ReturnType CCP1_Capture_Mode_Read_Value(uint16 *capture_value)
{
    Std_ReturnType ret = NOT_OK;
    CCP_REG_T capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
    if(NULL == capture_value){
        ret = NOT_OK;
    }
    else{
        /* Copy captured value */
        capture_temp_value.ccpr_low = CCPR1L;
        capture_temp_value.ccpr_high = CCPR1H;
        /* Write the 16-bit capture value */
        *capture_value = capture_temp_value.ccpr_16Bit;
        ret = OK;
    }
    return ret;
}
