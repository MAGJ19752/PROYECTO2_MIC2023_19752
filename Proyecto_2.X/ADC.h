/*
Archivo:        Proyecto2_2023
Dispositivo:    PIC16F887
Autor:		Mariel González Juárez (19752)
Compilador:     XC8, MPLABX 5.40
Programa:       Garra mecánica
*/


#ifndef __ADC__ 

#include <xc.h>

//inicializa el ADC

void ADC_Int(uint8_t ADFM_Select); // Seleccion del formato del resultado de la conversi�n

void ADC_Select(int channel); //Selecciona el canal de entrada del ADC.

void ADC_Isr_Enable(void); //Habilita la interrupci�n del ADC.

void ADC_Isr_Disable(void); //Deshabilita la interrupci�n del ADC
#endif 