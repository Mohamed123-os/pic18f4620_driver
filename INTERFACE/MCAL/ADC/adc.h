/* 
 * File:   adc.h
 * Author: mohamed
 *
 * Created on September 6, 2023, 8:32 PM
 */

#ifndef ADC_H
#define	ADC_H

/***************************includes section****************************************/
#include"../GPIO/gpio.h"
#include"../INTERRUPT/mcal_internal_interrupt.h"
/***************************macros sections*****************************************/
#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F

#define CONVERSION_IN_PROGRESS           1
#define CONVERSION_IDLE                  0

#define RIGHT_ADJUST                     1
#define LEFT_ADJUST                      0
#define ADC_VOLTAGE_REFERENCE_ENABLED    1
#define ADC_VOLTAGE_REFERENCE_DISABLED   0

#define ADC_CONVERSION_COMPLETED         1 
#define ADC_CONVERSION_INPROGRESS        0


/***************************function like macro section*****************************/
#define ADC_ENABLE()   ADCON0bits.ADON=1
#define ADC_DISABLE()   ADCON0bits.ADON=0

#define ADC_START_CONVERSION()  ADCON0bits.GODONE = 1
#define ADC_ENABLE_VOLTAGE_REFERENCE()  do{ADCON1bits.VCFG1 = 1;\
                                           ADCON1bits.VCFG0 = 1;\
                                        }while(0)
#define ADC_DISABLE_VOLTAGE_REFERENCE() do{ADCON1bits.VCFG1 = 0;\
                                           ADCON1bits.VCFG0 = 0;\
                                        }while(0)

#define ADC_RESULT_RIGHT_FORMAT()  (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()   (ADCON2bits.ADFM = 0)

/***************************data types section**************************************/
typedef enum{
    channel_0=0,
    channel_1,
    channel_2,
    channel_3,
    channel_4,
    channel_5,
    channel_6,
    channel_7,
    channel_8,
    channel_9,
    channel_10,
    channel_11,
    channel_12,        
}channel_select;

typedef enum
{
    clock_by_2=0,
    clock_by_8,
    clock_by_32,
    clock_RC,
    clock_by_4,
    clock_by_16,
    clock_by_64,
}clock_select;

typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}adc_acquisition_time_t;

typedef struct{
  void(*adc_interrupt_handler)(void);
  prioirty  priority_t;
  channel_select channel;  
  clock_select clock;
  adc_acquisition_time_t time;
  pin_config pin;
  uint8 voltage_reference ;             
  uint8 result_format ;  
}adc_t;
/***************************software interfaces section*****************************/
Std_ReturnType  Adc_init(const adc_t *adc );
Std_ReturnType  Adc_deinit(const adc_t *adc);
Std_ReturnType  Read(const adc_t *adc,uint16 *result);
Std_ReturnType  Read_on_interrupt(const adc_t *adc);



#endif	/* ADC_H */

