/*
Archivo:        Proyecto2_2023
Dispositivo:    PIC16F887
Autor:		Mariel González Juárez (19752)
Compilador:     XC8, MPLABX 5.40
Programa:       Garra mecánica
*/

#ifndef __EEPROM__
#define	__EEPROM__

#include <xc.h> 
#include <stdint.h>


uint8_t EEPROM_Read(uint8_t adress); //escribe un byte en la memoria EEPROM

void EEPROM_Write(uint8_t adress, uint8_t data); // Direcci�n de memoria de escritura. 
                                                 // Byte a escribir en la direcci�n especificada.


#endif