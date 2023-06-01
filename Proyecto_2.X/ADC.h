/*
Archivo:        Proyecto2_2023
Dispositivo:    PIC16F887
Autor:		Mariel GonzÃ¡lez JuÃ¡rez (19752)
Compilador:     XC8, MPLABX 5.40
Programa:       Garra mecÃ¡nica
*/


#ifndef __ADC__ 

#include <xc.h>

//inicializa el ADC

void ADC_Int(uint8_t ADFM_Select); // Seleccion del formato del resultado de la conversión

void ADC_Select(int channel); //Selecciona el canal de entrada del ADC.

void ADC_Isr_Enable(void); //Habilita la interrupción del ADC.

void ADC_Isr_Disable(void); //Deshabilita la interrupción del ADC
#endif 