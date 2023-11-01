#include"uart.h"
#if TX_INTERRPT_ENABLE == 1
static void(*tx_handler)(void)=NULL;
#endif
#if RX_INTERRPT_ENABLE == 1
static void(*rx_handler)(void)=NULL;
#endif
static void baud_rate_init(const uart_configs *configs );
static void TX_init(const uart_configs *configs );
static void RX_init(const uart_configs *configs );
/**
 * 
 * @param configs
 * @return 
 */
Std_ReturnType UART_INIT(const uart_configs *configs)
{
    Std_ReturnType ret=OK;
    if(NULL==configs)
    {
        ret=NOT_OK;
    }
    else
    {
        RCSTAbits.SPEN=0;
        TRISCbits.RC6=1;
        TRISCbits.RC7=1;
        baud_rate_init(configs);
        TX_init(configs );
        RX_init(configs ); 
        RCSTAbits.SPEN=1;
        
    }
    return ret;
    
}
/**
 * 
 * @param configs
 * @return 
 */
Std_ReturnType UART_DEINIT(const uart_configs *configs)
{
    Std_ReturnType ret=OK;
    if(NULL==configs)
    {
        ret=NOT_OK;
    }
    else
    {
         RCSTAbits.SREN=0;
    }
    return ret;
}
/**
 * 
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 *_data)
{
    Std_ReturnType ret=OK;
    if(NULL==_data)
    {
        ret=NOT_OK;
    }
    else
    {
        while(!PIR1bits.RCIF);
      *_data = RCREG;
    }
    return ret;
}
/**
 * 
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data)
{
    Std_ReturnType ret=OK;
    if(NULL==_data)
    {
        ret=NOT_OK;
    }
    else
    {
        if(1 == PIR1bits.RCIF){
        *_data = RCREG;
        ret = OK;
        }
    }
    return ret;
}


Std_ReturnType EUSART_ASYNC_RX_Restart(void)
{
    RCSTAbits.CREN = 0; /* Disables receiver */
    RCSTAbits.CREN = 1; /* Enables receiver */
}
/**
 * 
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYNC_WriteByteBlocking(uint8 _data)
{
    Std_ReturnType ret=OK;
    if(NULL==_data)
    {
        ret=NOT_OK;
    }
    else
    {
         while(!TXSTAbits.TRMT);
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
         EUSART_TX_InterruptEnable();
#endif
    TXREG = _data;
    }
    return ret;
}
/**
 * 
 * @param _data
 * @param str_len
 * @return 
 */
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8 *_data)
{
    Std_ReturnType ret=OK;
    if(NULL==_data)
    {
        ret=NOT_OK;
    }
    else
    {
        while(*_data!='\0')
        {
            EUSART_ASYNC_WriteByteBlocking(*_data);
            *_data++;
        }
        
    }
    return ret;
}
/**
 * 
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8 _data)
{
  Std_ReturnType ret=OK;
    if(NULL==_data)
    {
        ret=NOT_OK;
    }
    else
    {
        if(1 == PIR1bits.TXIF){
          TXREG=_data;
        ret = OK;
        }
    }
    return ret;  
}
/**
 * 
 * @param _data
 * @param str_len
 * @return 
 */
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data)
{
    Std_ReturnType ret=OK;
    if(NULL==_data)
    {
        ret=NOT_OK;
    }
    else
    {
        while(*_data!='\0')
        {
            if(1 == PIR1bits.TXIF){
             TXREG= *_data;
             __delay_ms(1);
            }
            *_data++;
        }
    }
    return ret;
}

/**
 * 
 * @param configs
 */
static void baud_rate_init(const uart_configs *configs )
{
    uint32 baud=0;
    switch(configs->baudrate_select)
    {
        case  BAUDRATE_ASYN_8BIT_lOW_SPEED:
            TXSTAbits.SYNC=ASYNCHRONUS;
            TXSTAbits.BRGH=ASYNCHRONUS_LOW_SPEED;
            BAUDCONbits.BRG16=_08BIT_BAUDRATE_GEN;
            baud=((_XTAL_FREQ / (float)configs->BaudRate) / 64) - 1;
        break;
        
        case  BAUDRATE_ASYN_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC=ASYNCHRONUS;
            TXSTAbits.BRGH=ASYNCHRONUS_HIGH_SPEED;
            BAUDCONbits.BRG16=_08BIT_BAUDRATE_GEN;
            baud=((_XTAL_FREQ / (float)configs->BaudRate) / 16) - 1;
        break;
        
        case  BAUDRATE_ASYN_16BIT_lOW_SPEED:
            TXSTAbits.SYNC=ASYNCHRONUS;
            TXSTAbits.BRGH=ASYNCHRONUS_LOW_SPEED;
            BAUDCONbits.BRG16=_16BIT_BAUDRATE_GEN;
            baud=((_XTAL_FREQ / (float)configs->BaudRate) / 16) - 1;
        break;
        
        case  BAUDRATE_ASYN_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC=ASYNCHRONUS;
            TXSTAbits.BRGH=ASYNCHRONUS_HIGH_SPEED;
            BAUDCONbits.BRG16=_16BIT_BAUDRATE_GEN;
            baud=((_XTAL_FREQ / (float)configs->BaudRate) / 4) - 1;
        break;
        
        case BAUDRATE_SYN_8BIT:
            TXSTAbits.SYNC = SYNCHRONUS;
            BAUDCONbits.BRG16 = _08BIT_BAUDRATE_GEN;
            baud = ((_XTAL_FREQ / (float)configs->BaudRate) / 4) - 1;
            break;
        case BAUDRATE_SYN_16BIT:
            TXSTAbits.SYNC = SYNCHRONUS;
            BAUDCONbits.BRG16 = _16BIT_BAUDRATE_GEN;
            baud = ((_XTAL_FREQ / (float)configs->BaudRate) / 4) - 1;
            break;
            
    }
    SPBRG=(uint8)((uint32)baud);
    SPBRGH=(uint8)(((uint32)baud)>>8);
}


/**
 * 
 * @param configs
 */
static void TX_init(const uart_configs *configs )
{
    if(configs->tx_choose_configs.tx_enable==TRANSMIT_ENABLE)
    {
        TXSTAbits.TXEN=TRANSMIT_ENABLE ;
    }
    if(configs->tx_choose_configs.tx_9_bits_enable==TRANSMIT_9_BITS)
    {
        TXSTAbits.TX9=TRANSMIT_9_BITS;
    }
    else if(configs->tx_choose_configs.tx_9_bits_enable==TRANSMIT_8_BITS)
    {
        TXSTAbits.TX9=TRANSMIT_8_BITS;
    }
    
    
    if(TRANSMIT_INTERRUPT_ENABLE == configs->tx_choose_configs.tx_interrupt_enable){
            PIE1bits.TXIE = TRANSMIT_INTERRUPT_ENABLE;
            /* Interrupt Configurations */ 
#if TX_INTERRPT_ENABLE==1
            EUSART_TX_InterruptEnable();
            /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==1 
            Priority_levels_enable();
            if(HIGH_PRIORITY == configs->tx_choose_configs.tx_priority){
                /* Enables all high-priority interrupts */
                Priorit_high_enable();
                EUSART_TX_HighPrioritySet();
            }
            else if(LOW_PRIORITY == configs->tx_choose_configs.tx_priority){
                /* Enables all unmasked peripheral interrupts */
                 Priorit_low_enable();
                EUSART_TX_LowPrioritySet();
            }
            else{ /* Nothing */ }
#else
           Global_interrupt_enable();
            pripherals_interrupt_enable();
#endif
            tx_handler=configs->TX_interrupt_handler;
#endif
        }
        else if(TRANSMIT_INTERRUPT_DISABLE == configs->tx_choose_configs.tx_interrupt_enable){
            PIE1bits.TXIE = TRANSMIT_INTERRUPT_DISABLE;
        }
        else{ /* Nothing */}

}
/**
 * 
 * @param configs
 */
static void RX_init(const uart_configs *configs )
{
    if(configs->rx_choose_configs.rx_enable==ENABLE_RECEIVE)
    {
        RCSTAbits.CREN=ENABLE_RECEIVE ;
    }
    if(configs->rx_choose_configs.rx_9_bits_enable==RECEIVE_9_BIT)
    {
        RCSTAbits.RC9=RECEIVE_9_BIT;
    }
    else if(configs->rx_choose_configs.rx_9_bits_enable==REVEIVER_8_BITS)
    {
        RCSTAbits.RC9=REVEIVER_8_BITS;
    }
    
    
    
     
    if(RECEIVE_INTERRUPT_ENABLE  == configs->rx_choose_configs.rx_interrupt_enable)
    {
            PIE1bits.RCIE = RECEIVE_INTERRUPT_ENABLE;
            /* Interrupt Configurations */ 
#if RX_INTERRPT_ENABLE==1
            EUSART_RX_InterruptEnable();
            /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==1 
            Priority_levels_enable();
            if(HIGH_PRIORITY == configs->rx_choose_configs.rx_priority)
            {
                /* Enables all high-priority interrupts */
                Priorit_high_enable();
                EUSART_RX_HighPrioritySet();
            }
            else if(LOW_PRIORITY == configs->rx_choose_configs.rx_priority)
            {
                /* Enables all unmasked peripheral interrupts */
                Priorit_low_enable();
                EUSART_RX_LowPrioritySet();
            }
            else{ /* Nothing */ }
#else
           Global_interrupt_enable();
           pripherals_interrupt_enable();
#endif
           rx_handler=configs->RX_interrupt_handler;
#endif
    }
        else if(RECEIVE_INTERRUPT_DISABLE == configs->rx_choose_configs.rx_interrupt_enable)
        {
            PIE1bits.RCIE = RECEIVE_INTERRUPT_DISABLE;
        }
        else{ /* Nothing */}
}
#if TX_INTERRPT_ENABLE == 1
void EUSART_TX_ISR(void){
    EUSART_TX_InterruptDisable();
    if(tx_handler){
        tx_handler();
    }else { /* Nothing */}
}
#endif

#if RX_INTERRPT_ENABLE == 1
void EUSART_RX_ISR(void){
    if(rx_handler){
        rx_handler();
    }else { /* Nothing */}
}
#endif