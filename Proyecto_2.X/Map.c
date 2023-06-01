/*
Archivo:        Proyecto2_2023
Dispositivo:    PIC16F887
Autor:		Mariel González Juárez (19752)
Compilador:     XC8, MPLABX 5.40
Programa:       Garra mecánica
*/

#include "Map.h"

unsigned short map(uint8_t x, uint8_t x0, uint8_t x1,unsigned short y0, unsigned short y1)
{
    return (unsigned short)(y0+((float)(y1-y0)/(x1-x0))*(x-x0));
}