
#include"spi.h"


/**
 * 
 * @param configs
 * @return 
 */
Std_ReturnType SPI_Master_Init(const spi_conf *configs)
{
    Std_ReturnType ret=OK;
    if(NULL==configs)
    {
        ret=NOT_OK;
    }
    else
    {
        /*disable spi*/
        SSPCON1bits.SSPEN=0;
        
        /*configre pins directions */
        pin_directoin_intialize(&(configs->CLOCK));
        pin_directoin_intialize(&(configs->SDI));
        pin_directoin_intialize(&(configs->SDO));
        pin_directoin_intialize(&(configs->SS));
        
        /*configure idle state*/
        if(configs->clck_mode==IDLE_HIGH)
        {
           SSPCON1bits.CKP=IDLE_HIGH;
        }
        else if(configs->clck_mode==IDLE_LOW)
        {
            SSPCON1bits.CKP=IDLE_LOW;
        }
        else
        {
            /*no thing*/
        }
        
       /* configure clock source */
        SSPCON1bits.SSPM=configs->clck_mode;
        
        /*configue transmit edge */
        if(configs->active_idle==ACTIVE_TO_IDLE)
        {
            SSPSTATbits.CKE=ACTIVE_TO_IDLE;
        }
        else if(configs->active_idle==IDLE_TO_ACTIVE)
        {
            SSPSTATbits.CKE=IDLE_TO_ACTIVE;
        }
        else
        {
            /*no thing */
        }
        
        /*enable spi*/
        PIR1bits.SSPIF=0;
        
        
        // configure sample 
        SSPSTATbits.SMP=configs->sample;
        //enable spi
        SSPCON1bits.SSPEN=1;
    }
    return ret;
}
/**
 * 
 * @param configs
 * @return 
 */
Std_ReturnType SPI_Slave_Init(const spi_conf *configs)
{
   Std_ReturnType ret=OK;
    if(NULL==configs)
    {
        ret=NOT_OK;
    }
    else
    {
        /*disable spi*/
        SSPCON1bits.SSPEN=0;
        
        /*configre pins directions */
        pin_directoin_intialize(&(configs->CLOCK));
        pin_directoin_intialize(&(configs->SDI));
        pin_directoin_intialize(&(configs->SDO));
        pin_directoin_intialize(&(configs->SS));
        
        /*configure idle state*/
        if(configs->clck_mode==IDLE_HIGH)
        {
           SSPCON1bits.CKP=IDLE_HIGH;
        }
        else if(configs->clck_mode==IDLE_LOW)
        {
            SSPCON1bits.CKP=IDLE_LOW;
        }
        else
        {
            /*no thing*/
        }
        
       /* configure clock source */
        SSPCON1bits.SSPM=configs->clck_mode;
        
        /*configue transmit edge */
        if(configs->active_idle==ACTIVE_TO_IDLE)
        {
            SSPSTATbits.CKE=ACTIVE_TO_IDLE;
        }
        else if(configs->active_idle==IDLE_TO_ACTIVE)
        {
            SSPSTATbits.CKE=IDLE_TO_ACTIVE;
        }
        else
        {
            /*no thing */
        }
        
        /*enable spi*/
        PIR1bits.SSPIF=0;
        SSPCON1bits.SSPEN=1;
    }
    return ret; 
}
/**
 * 
 * @param value
 * @return 
 */
Std_ReturnType SPI_Write(uint8 value)
{
    uint8 data_flush;
    SSPBUF=value;			/* Copy data in SSBUF to transmit */
    while(!PIR1bits.SSPIF);	/* Wait for complete 1 byte transmission */
    PIR1bits.SSPIF=0;      /* Clear SSPIF flag */
    data_flush=SSPBUF;		/* Flush the data */
}
/**
 * 
 * @param value
 * @return 
 */
Std_ReturnType SPI_Read(uint8 *value)
{
    Std_ReturnType ret=OK;
    if(NULL==value)
    {
        ret=NOT_OK;
    }
    else
    {
        SSPBUF=0xff;		/* Copy flush data in SSBUF */
        while(!PIR1bits.SSPIF);	/* Wait for complete 1 byte transmission */
        PIR1bits.SSPIF=0;
        *value =SSPBUF;
        
    }
    return ret;
}