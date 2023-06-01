/*
Archivo:        Proyecto2_2023
Dispositivo:    PIC16F887
Autor:		Mariel Gonz√°lez Ju√°rez (19752)
Compilador:     XC8, MPLABX 5.40
Programa:       Garra mec√°nica
*/

#ifndef __EEPROM__
#define	__EEPROM__

#include <xc.h> 
#include <stdint.h>


uint8_t EEPROM_Read(uint8_t adress); //escribe un byte en la memoria EEPROM

void EEPROM_Write(uint8_t adress, uint8_t data); // DirecciÛn de memoria de escritura. 
                                                 // Byte a escribir en la direcciÛn especificada.


#endif