/*
Archivo:        Proyecto2_2023
Dispositivo:    PIC16F887
Autor:		Mariel González Juárez (19752)
Compilador:     XC8, MPLABX 5.40
Programa:       Garra mecánica
*/

#include <xc.h>


uint8_t EEPROM_Read(uint8_t adress)
{
    while(EECON1bits.RD || EECON1bits.WR);
    EECON1bits.EEPGD = 0;           
    EEADR = adress; 
    EECON1bits.RD = 1;            
    return EEDAT;                  
}


void EEPROM_Write(uint8_t adress, uint8_t data)
{
    while(EECON1bits.WR);  
    EECON1bits.EEPGD = 0;          
    EECON1bits.WREN = 1;          
    EEADR = adress;
    EEDAT = data;
    
    INTCONbits.GIE = 0;            
    EECON2 = 0x55;
    EECON2 = 0xAA;

    EECON1bits.WR = 1;              

    INTCONbits.GIE = 1;             
    EECON1bits.WREN = 0;  
    INTCONbits.RBIF = 0;
}