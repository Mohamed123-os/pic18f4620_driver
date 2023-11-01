#include"eeprom.h"
/**
 * 
 * @param address
 * @param data
 * @return 
 */
Std_ReturnType EEPROM_Write(uint16 address, uint8 data)
{
    Std_ReturnType ret = NOT_OK;
    if(NULL == data){
        ret = NOT_OK;
    }
    else
    {
        uint8 interrupt_state=INTCONbits.GIE;             //save state of the interrupt 
        EEADRH=(uint8)((address>>8)&0x03);                //intialize address
        EEADR= (uint8)(address&0xFF);                     //intialize address
        EEDATA=data;                                      //write data to eedata register
        EECON1bits.CFGS=0;                                //access eeprom
        EECON1bits.EEPGD=0;                               //access eebrom
        EECON1bits.WREN=1;                                //allow write in falsh or eeprom
        INTCONbits.GIE=0 ;                                //disabel global interrupt
        EECON2=0x55;                                      //from data sheet
        EECON2=0xAA;                                      //from data sheet
        EECON1bits.WR=1;                                  //itialize writing
        while(EECON1bits.WR==1);                          //writing is done now 
        EECON1bits.WREN =0;                               //disable writing in eeprom
        INTCONbits.GIE=interrupt_state;                   //return interrupt state 
        
    }
   
    return ret;
}



/**
 * 
 * @param address
 * @param data
 * @return 
 */
Std_ReturnType EEPROM_Read(uint16 address, uint8 *data)
{
    Std_ReturnType ret = NOT_OK;
    if(NULL == data){
        ret = NOT_OK;
    }
    else
    {
        EEADRH=(uint8)((address>>8)&0x03);                //intialize address
        EEADR= (uint8)(address&0xFF);                     //intialize address
        EECON1bits.CFGS=0;                                //access eeprom
        EECON1bits.EEPGD=0;                               //access eebrom
        EECON1bits.RD=1;                                  //alloq read
        NOP();                                            //wait no operation cycle
        NOP();                                            //wait no operation cycle
        *data=EEDATA;                                     //read data from eedata register
    }
    return ret;
}
