/*
Archivo:        Proyecto2_2023
Dispositivo:    PIC16F887
Autor:		Mariel González Juárez (19752)
Compilador:     XC8, MPLABX 5.40
Programa:       Garra mecánica
*/
#include "ADC.h"

void ADC_Init(uint8_t ADFM_Select)
{
    ADCON0 = 0b10000001;                // Enciende ADC y FOSC/32 como ADCS
    ADCON1bits.ADFM = ADFM_Select;       // Justificado a la izquierda
    ADCON1bits.VCFG1 = 0;
    ADCON1bits.VCFG0 = 0;               // Voltajes de referencia como VDD y VSS
}

void ADC_SelectChannel(int channel)
{
    ADCON0bits.CHS = channel & 0x0F;     // Selecciona el canal de entrada del ADC
}

void ADC_EnableInterrupt(void)
{
    PIR1bits.ADIF = 0;                   // Limpia la bandera de interrupci�n del ADC
    PIE1bits.ADIE = 1;                   // Habilitar interrupciones del ADC
}

void ADC_DisableInterrupt(void)
{
    PIE1bits.ADIE = 0;                   // Deshabilitar interrupciones del ADC
}