/*
Archivo:        Proyecto2_2023
Dispositivo:    PIC16F887
Autor:		Mariel Gonz√°lez Ju√°rez (19752)
Compilador:     XC8, MPLABX 5.40
Programa:       Garra mec√°nica
*/

#include <xc.h>

void PWM_config(char canal, int periodo)
{
    CCP1CON = 0;  
    CCP2CON = 0;                        // Apagar ambos mÛdulos CCP
    
    switch (periodo)
    {
        case 2:
            PR2 = 125;
            break;
        case 3:
            PR2 = 188; 
            break;
        case 4:
            PR2 = 250; 
            break;
        default:
            PR2 = 63;                  
    }                                   // Se selecciona entre 3 casos de 2, 3 y 4 ms para el periodo y un valor predeterminado de 1 ms
    
    if (canal == 1 || canal == 3)       // ConfiguraciÛn para el canal 1 o ambos canales
    {
        CCP1CONbits.P1M = 0;            // Modo de salida simple
        CCP1CONbits.CCP1M = 0b1100;     // Modo PWM
    }
    if (canal == 2 || canal == 3)       // ConfiguraciÛn para el canal 2 o ambos canales
    {
        CCP2CONbits.CCP2M = 0b1100;     // Modo PWM
    }
    
    PIR1bits.TMR2IF = 0;                // Bandera TMR2
    
    T2CONbits.T2CKPS = 0b11;            // Prescaler 1:16
    T2CONbits.TMR2ON = 1;               // Iniciar TMR2
    
    while (!PIR1bits.TMR2IF);           // Esperar a que se complete un ciclo del TMR2
    PIR1bits.TMR2IF = 0;
}

void PWM_duty(char canal, unsigned short duty)
{
    if (canal == 1 || canal == 3)       // ConfiguraciÛn para el canal 1 o ambos canales
    {
        CCPR1L = duty >> 2;              // Desplazar 2 bits a la derecha para obtener el ciclo de trabajo
        CCP1CONbits.DC1B = duty & 3;     // Realizar una operaciÛn AND con los dos bits menos significativos y asignarlos
    }
    if (canal == 2 || canal == 3)       // ConfiguraciÛn para el canal 2 o ambos canales
    {
        CCPR2L = duty >> 2;              // Desplazar 2 bits a la derecha para obtener el ciclo de trabajo
        CCP2CONbits.DC2B0 = duty & 0b01;
        CCP2CONbits.DC2B1 = duty & 0b10; // Realizar una operaciÛn AND con los dos bits menos significativos y asignarlos
    }
}

void PWM_Enable_Mux()
{
    PSTRCONbits.STRSYNC = 1;    
}

void PWM_Disable_Mux()
{
    PSTRCONbits.STRSYNC = 0;    
}

void PWM_Mux_Channel_Select(int channel)
{
    PSTRCONbits.STRA = (channel == 0) ? 1 : 0;
    PSTRCONbits.STRB = (channel == 1) ? 1 : 0;
    PSTRCONbits.STRC = (channel == 2) ? 1 : 0;
    PSTRCONbits.STRD = (channel == 3) ? 1 : 0;