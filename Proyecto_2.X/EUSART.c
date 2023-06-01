/*
Archivo:        Proyecto2_2023
Dispositivo:    PIC16F887
Autor:		Mariel Gonz�lez Ju�rez (19752)
Compilador:     XC8, MPLABX 5.40
Programa:       Garra mec�nica
*/

#include <xc.h>

void EUSART_Init(void)
{
    SPBRGH = 0;
    SPBRG = 25;                 // Se establece a 9600 baudrate a 4MHz de velocidad de oscilador
    
    RCSTA = 0x90;               // Habilitar los pines para comunicaci�n UART, habilitar receptor
    
    TXSTA = 0x26;               // Habilitar transmisor, modo as�ncrono, alta velocidad, detecci�n de bits de sincronizaci�n adicionales
    
    BAUDCON = 0x08;             // Deshabilitar bits de salto
    
    RCSTA1bits.SPEN = 1;        // Habilitar el m�dulo EUSART
}

void EUSART_Enable_TX_Isr(void)
{
    PIE1bits.TXIE = 1;          // Habilitar interrupciones de transmisi�n UART
}

void EUSART_Enable_RX_Isr(void)
{
    PIE1bits.RCIE = 1;          // Habilitar interrupciones de recepci�n UART
}

void EUSART_Disable_TX_Isr(void)
{
    PIE1bits.TXIE = 0;          // Deshabilitar interrupciones de transmisi�n UART
}

void EUSART_Disable_RX_Isr(void)
{
    PIE1bits.RCIE = 0;          // Deshabilitar interrupciones de recepci�n UART
}

void Enviar_Texto(unsigned char *text)
{
    while (*text != '\0')                       // Mientras el texto no se termine
    {
        while (!TX1IF);                          // Mientras la bandera de transmisi�n no est� activa
        TX1REG = *text;                          // Enviar caracter por UART
        text++;                                  // Aumentar la posici�n del caracter del string
    }
}

void Recibir_Texto(char* Output, unsigned int maxLength)
{
    unsigned int i;
    for (i = 0; i < maxLength; i++)
    {
        while (!RC1IF);                          // Esperar a la bandera de recepci�n
        Output[i] = RC1REG;                       // Leer el dato recibido

        if (Output[i] == '\r')                     // Si el dato recibido es un retorno de carro
            break;
    }
    Output[i] = '\0';                             // Agregar el car�cter nulo al final del string
}

int string_to_int(char* str)
{
    return atoi(str);                             // Convertir una cadena de caracteres a un entero
}