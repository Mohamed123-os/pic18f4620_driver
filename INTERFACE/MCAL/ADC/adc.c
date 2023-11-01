#include "adc.h"

/**
 * 
 * @param adc
 * @param channel
 * @return 
 */
static inline Std_ReturnType set_channel_as_analog(const adc_t *adc);

#if ADC_INTERRUPT_ENABLE ==1 
static void (*adc_interrupt_handle)(void)=NULL;
#endif


Std_ReturnType  Adc_init(const adc_t *adc )
{
    Std_ReturnType ret=OK;
    if(adc==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
       ADC_DISABLE() ;                            //disabel adc
       pin_directoin_intialize(&(adc->pin));      //intialize pin 
       set_channel_as_analog(adc);                //SET channel as analog
       ADCON0bits.CHS=adc->channel;               //choose input channel
       ADCON2bits.ACQT=adc->time;                 //select acquisation time 
       ADCON2bits.ADCS=adc->clock;                //select clock for acquisation time 
       ADCON1bits.VCFG=adc->voltage_reference;    //select voltage refrence
       
       switch(adc->result_format)                 //select result format 
       {
           case RIGHT_ADJUST: ADC_RESULT_RIGHT_FORMAT(); break;
           case LEFT_ADJUST:  ADC_RESULT_LEFT_FORMAT(); break;
           default:ADC_RESULT_RIGHT_FORMAT();
       }
       
#if ADC_INTERRUPT_ENABLE ==1                        //if adc interrupt is on
       ADC_InterruptEnable();                       //enable adc interrupt 
       ADC_InterruptFlagClear();                   //clear adc flag 
        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==1             //if priority levels is on
       Priority_levels_enable();                    //enabel priority levels 
       switch(adc->priority_t)                      //select priority
       {
           case HIGH_PRIORITY: Priorit_high_enable(); ADC_HighPrioritySet(); break; //enable adc high priority
           case LOW_PRIORITY : Priorit_low_enable();  ADC_LowPrioritySet(); break;  //enable adc low priority
       }
#else 
       Global_interrupt_enable();
       pripherals_interrupt_enable();
#endif
       adc_interrupt_handle=adc->adc_interrupt_handler;
#endif      
       ADC_ENABLE();                        //enabel adc module          
    }
   
   return ret; 
}

/**
 * 
 * @param adc
 * @return 
 */
Std_ReturnType  Adc_deinit(const adc_t *adc)
{
    Std_ReturnType ret=OK;
    if(adc==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
       ADC_DISABLE() ;           //diabel adc
    }
   
   return ret; 
    
}
/**
 * 
 * @param adc
 * @param result
 * @return 
 */
Std_ReturnType  Read(const adc_t *adc,uint16 *result)
{
    Std_ReturnType ret=OK;
    if(adc==NULL||result==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
       ADC_START_CONVERSION()  ; //start conversion;
       while(ADCON0bits.GO_nDONE);  //wait conversion to finish
       
       if(adc->result_format==RIGHT_ADJUST)
       {
           *result=(uint16)((ADRESH << 8) + ADRESL); //RESULT FORMAT ADJUST RIGHT
           
       }
       else if(adc->result_format==LEFT_ADJUST)
       {
           *result=(uint16)(((ADRESH << 8) + ADRESL) >> 6); //RESULT FORMAT ADJUST LEFT 
           
       }
        else
        {
            *result = (uint16)((ADRESH << 8) + ADRESL);  //DEFAULT RESULT FORMAT ADJUST RIGHT
        }
    }
   
   return ret; 
}
/**
 * 
 * @param adc
 * @param result
 * @return 
 */
Std_ReturnType  Read_on_interrupt(const adc_t *adc)
{
    Std_ReturnType ret=OK;
    if(adc==NULL )
    {
        ret=NOT_OK;
    }
    else
    {
         ADC_START_CONVERSION()  ; //start conversion;
       
    }
   
   return ret; 
}

static inline Std_ReturnType set_channel_as_analog(const adc_t *adc)
{
    Std_ReturnType ret=OK;
    if(adc==NULL)
    {
        ret=NOT_OK;
    }
    else
    {
        switch(adc->channel)
        {
            case channel_0:ADCON1bits.PCFG=ADC_AN0_ANALOG_FUNCTIONALITY;break;
            case channel_1:ADCON1bits.PCFG=ADC_AN1_ANALOG_FUNCTIONALITY;break;
            case channel_2:ADCON1bits.PCFG=ADC_AN2_ANALOG_FUNCTIONALITY;break;
            case channel_3:ADCON1bits.PCFG=ADC_AN3_ANALOG_FUNCTIONALITY;break;
            case channel_4:ADCON1bits.PCFG=ADC_AN4_ANALOG_FUNCTIONALITY;break;
            case channel_5:ADCON1bits.PCFG=ADC_AN5_ANALOG_FUNCTIONALITY;break;
            case channel_6:ADCON1bits.PCFG=ADC_AN6_ANALOG_FUNCTIONALITY;break;
            case channel_7:ADCON1bits.PCFG=ADC_AN7_ANALOG_FUNCTIONALITY;break;
            case channel_8:ADCON1bits.PCFG=ADC_AN8_ANALOG_FUNCTIONALITY;break;
            case channel_9:ADCON1bits.PCFG=ADC_AN9_ANALOG_FUNCTIONALITY;break;
            case channel_10:ADCON1bits.PCFG=ADC_AN10_ANALOG_FUNCTIONALITY;break;
            case channel_11:ADCON1bits.PCFG=ADC_AN11_ANALOG_FUNCTIONALITY;break;
            case channel_12:ADCON1bits.PCFG=ADC_AN12_ANALOG_FUNCTIONALITY;break;
            default:ADCON1bits.PCFG=ADC_ALL_ANALOG_FUNCTIONALITY;break;
        }
    }
   return ret; 
}
#if ADC_INTERRUPT_ENABLE ==1 
void ADC_ISR(void){
    ADC_InterruptFlagClear();       //CLEAR FLAG FOR ADC
    if(adc_interrupt_handle){
        adc_interrupt_handle();  //CALL CALL BACK FUNCTION
    }
}
#endif