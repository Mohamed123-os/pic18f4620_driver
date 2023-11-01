/* 
 * File:   uart.h
 * Author: mohamed
 *
 * Created on September 22, 2023, 2:12 PM
 */

#ifndef UART_H
#define	UART_H

/***************************includes section****************************************/
#include "../GPIO/gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h" 
/***************************macros sections*****************************************/
// UART operation modes
#define SYNCHRONUS                0x01
#define ASYNCHRONUS               0X00

// UART speed modes
#define ASYNCHRONUS_HIGH_SPEED    0x01
#define ASYNCHRONUS_LOW_SPEED     0X00

// UART data bits modes
#define TRANSMIT_9_BITS           0X01
#define TRANSMIT_8_BITS           0X00

// UART transmission control
#define TRANSMIT_ENABLE           0X01
#define TRANSMIT_DISABLE          0X00

// UART baud rate speed
#define HIGH_SPEED_BAUD_REATE    0X01
#define LOW_SPEED_BAUD_REATE     0X00

// UART transmit shift register status
#define TX_SHIFT_REGISTER_EMPTY        0X01
#define TX_SHIFT_REGISTER_FULL         0X00

// UART serial port control
#define SERIAL_PORT_ENABLE        0X01
#define SERIAL_PORT_DIABLE        0X00

// UART receive data bits modes
#define RECEIVE_9_BIT         0X01
#define REVEIVER_8_BITS       0X00

// UART receive control
#define ENABLE_RECEIVE       0X01
#define DIABEL_REVEIVE       0X00

// UART error status flags
#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0

#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0

// UART baud rate generation options
#define _16BIT_BAUDRATE_GEN  		1
#define _08BIT_BAUDRATE_GEN  		0

// UART transmit and receive interrupt control
#define TRANSMIT_INTERRUPT_ENABLE   1
#define TRANSMIT_INTERRUPT_DISABLE   0

#define RECEIVE_INTERRUPT_ENABLE   1
#define RECEIVE_INTERRUPT_DISABLE   0
/***************************function like macro section*****************************/
/***************************data types section**************************************/
typedef enum{
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;

typedef struct{
    uint8 tx_enable;
    uint8 tx_9_bits_enable;
    uint8 tx_interrupt_enable;
    prioirty tx_priority;
}TX_congigs;

typedef struct{
    uint8 rx_enable;
    uint8 rx_9_bits_enable;
    uint8 rx_interrupt_enable;
    prioirty rx_priority;
}RX_congigs;

typedef struct{
    
    uint32 BaudRate;
    TX_congigs tx_choose_configs;
    RX_congigs rx_choose_configs;
    baudrate_gen_t baudrate_select;
    #if TX_INTERRPT_ENABLE == 1
void(*TX_interrupt_handler)(void);
#endif
#if TX_INTERRPT_ENABLE == 1
    void(*RX_interrupt_handler)(void);
#endif
}uart_configs;

/***************************software interfaces section*****************************/

Std_ReturnType UART_INIT(const uart_configs *configs);
Std_ReturnType UART_DEINIT(const uart_configs *configs);

Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 *_data);
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data);
Std_ReturnType EUSART_ASYNC_RX_Restart(void);

Std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint8 _data);
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8 *_data);
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8 _data);
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data);



#endif	/* UART_H */

