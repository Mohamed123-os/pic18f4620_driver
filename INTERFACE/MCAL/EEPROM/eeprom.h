/* 
 * File:   eeprom.h
 * Author: mohamed
 *
 * Created on September 5, 2023, 11:31 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

/***************************includes section****************************************/
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/INTERRUPT/mcal_internal_interrupt.h"
/***************************macros sections*****************************************/
/* Flash Program or Data EEPROM Memory Select  */
#define ACCESS_FLASH_PROGRAM_MEMORY       1
#define ACCESS_EEPROM_PROGRAM_MEMORY      0
/* Flash Program/Data EEPROM or Configuration Select */
#define ACCESS_CONFIG_REGISTERS           1
#define ACCESS_FLASH_EEPROM_MEMORY        0
/* Flash Program/Data EEPROM Write Enable */
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM   1
#define INHIBTS_WRITE_CYCLES_FLASH_EEPROM 0
/* Write Control */
#define INITIATE_DATA_EEPROM_WRITE_ERASE  1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED 0
/* Read Control */
#define INITIATE_DATA_EEPROM_READ         1
/***************************function like macro section*****************************/
/***************************data types section**************************************/
/***************************software interfaces section*****************************/
Std_ReturnType EEPROM_Write(uint16 address, uint8 data);
Std_ReturnType EEPROM_Read(uint16 address, uint8 *data);

#endif	/* EEPROM_H */

