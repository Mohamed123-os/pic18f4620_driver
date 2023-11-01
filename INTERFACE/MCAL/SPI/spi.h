/* 
 * File:   spi.h
 * Author: mohamed
 *
 * Created on October 11, 2023, 11:41 AM
 */

#ifndef SPI_H
#define	SPI_H

/***************************includes section****************************************/
#include"../GPIO/gpio.h"
#include"../INTERRUPT/mcal_internal_interrupt.h"
/***************************macros sections*****************************************/
#define MASTER                            1
#define SLAVE                             0

#define SAMPLE_AT_END                     1
#define SAMPLE_AT_MIDDLE                  0

#define ACTIVE_TO_IDLE                    1
#define IDLE_TO_ACTIVE                    0

#define RECEIVE_COMPLETE                  1
#define RECEIVE_NOT_COMPLETE              0

#define IDLE_HIGH                         1
#define IDLE_LOW                          0

#define ENABLE_SPI                        1
#define DISABLE_SPI                       0

#define OVERFLOW                          1
#define NO_OVERFLOW                       0

#define COLLOSION                         1
#define NO_COLLOSION                      0


/***************************function like macro section*****************************/
/***************************data types section**************************************/
typedef enum{
    SPI_Master_mode_Fosc4,
    SPI_Master_mode_Fosc16,
	SPI_Master_mode_Fosc64,
	SPI_Master_mode_TMR2_output_by_2,
    SPI_Slave_mode_SS_enabled,
	SPI_Slave_mode_SS_disabled_I_O
}mode_and_osc;

typedef struct {
   mode_and_osc clck_mode;
   uint8 idle_state;
   uint8 active_idle;
   pin_config SDI;
   pin_config SDO;
   pin_config CLOCK;
   pin_config SS;
   uint8 sample;
}spi_conf;
/***************************software interfaces section*****************************/
Std_ReturnType SPI_Master_Init(const spi_conf *configs);
Std_ReturnType SPI_Slave_Init(const spi_conf *configs);
Std_ReturnType SPI_Write(uint8 value);
Std_ReturnType SPI_Read(uint8 *value);



#endif	/* SPI_H */

