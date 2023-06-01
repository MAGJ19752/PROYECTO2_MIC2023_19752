/*
Archivo:        Proyecto2_2023
Dispositivo:    PIC16F887
Autor:		Mariel González Juárez (19752)
Compilador:     XC8, MPLABX 5.40
Programa:       Garra mecánica
Hardware:	     4 servos, 4 potenciometros, LEDS
Creado:         20/05/2023
Ultima modificacion: 01/06/2023 */
//******************************************************************************
// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
//******************************************************************************

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF
// CONFIG2
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//******************************************************************************
// Includes
//******************************************************************************
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pic16f887.h>    //Se incluyen las librerias necesarias

#include "ADC.h"
#include "Map.h"
#include "PWM.h"
#include "EUSART.h"     //Funciones propias
#include "EEPROM.h"
//******************************************************************************
// Definiciones
//******************************************************************************
#define _XTAL_FREQ 4000000  //Se establece el oscilador a 4.0Mhz

//******************************************************************************
// Variables
//******************************************************************************
uint8_t  VAL_TMR0 = 185;           //Precarga TMR0
uint8_t  ADCF = 0;          //Bandera para rotacion de ADC
uint8_t  SEL[1];
uint8_t  F1 = 0;
uint8_t  F2 = 1;
uint8_t  F3 = 1;


unsigned short Ser1 = 0;
unsigned short Ser2 = 0;
unsigned short Ser3 = 0;
unsigned short Ser4 = 0;     //Variables para almacenar Duty Cicle

uint8_t Posicion_S[4];


//******************************************************************************
// Interrupciones
//******************************************************************************
void __interrupt() isr(void)
{
    if (RBIF)
    {
        if (!RB0)
        {
            F1 = (F1 + 1) % 4;
            PORTB = (PORTB & 0x0F) | (1 << (F1 + 4));
        }
        RBIF = 0;
    }



    if (PORTBbits.RB4 == 1)
    {
    if (ADIF)                                       //Chequea bandera de interrupcion de ADC
    {
        if (ADCF == 0)                       //En caso ADCF
        {
            Posicion_S[0] = ADRESH;                          //Lee ADC y almacena en ADC0 la lectura del primer potenciometro
            Ser1 = map(Posicion_S[0],0,255,160,650);   //Mapeo para los rangos a los cuales trabaja el servo de PWM
            PWM_duty(1,Ser1);                 //Funcion para seleccionar canal y enviar valor PWM
            PWM_Mux_Channel_Select(0);
            ADCF = 1;                        //Rotar bandera ADC
        }
        else if (ADCF == 1)
        {
            Posicion_S[1] = ADRESH;                          //Lee ADC y almacena en ADC1 la lectura del primer potenciometro
            Ser2 = map(Posicion_S[1],0,255,160,650);   //Mapeo para los rangos a los cuales trabaja el servo de PWM
            PWM_duty(1,Ser2);                 //Funcion para seleccionar canal y enviar valor PWM
            PWM_Mux_Channel_Select(1);
            ADCF = 2;                        //Rotar bandera ADC
        }
        else if (ADCF == 2)
        {
            Posicion_S[2] = ADRESH;                          //Lee ADC y almacena en ADC2 la lectura del primer potenciometro
            Ser3 = map(Posicion_S[2],0,255,160,650);   //Mapeo para los rangos a los cuales trabaja el servo de PWM
            PWM_duty(1,Ser3);                 //Funcion para seleccionar canal y enviar valor PWM
            PWM_Mux_Channel_Select(2);
            ADCF = 3;                        //Rotar bandera ADC
        }
        else if (ADCF == 3)
        {
            Posicion_S[3] = ADRESH;                          //Lee ADC y almacena en ADC3 la lectura del primer potenciometro
            Ser4 = map(Posicion_S[3],0,255,160,650);   //Mapeo para los rangos a los cuales trabaja el servo de PWM
            PWM_duty(1,Ser4);                 //Funcion para seleccionar canal y enviar valor PWM
            PWM_Mux_Channel_Select(3);
            ADCF = 0;                        //Rotar bandera ADC
        }
        ADIF = 0;                                   //Reinicia bandera ADC
        F2 = 1;
        F3 = 1;
    }
    }

    else if (PORTBbits.RB5 == 1)
    {
        if (F2 == 1)
        {
            Enviar_Texto(" Menu EEPROM \n");
            Enviar_Texto("Presione Boton 2 para guardar posicion y boton 3 para llamar a posicion \n");
            F2 = 0;
        }
        if (RBIF)
        {
            if (!RB1)
            {
                Enviar_Texto("Escribiendo EEPROM \n");
                PORTEbits.RE0 = 0;
                PORTEbits.RE1 = 1;
                EEPROM_Write(0x00, Posicion_S[0]);
                EEPROM_Write(0x01, Posicion_S[1]);
                EEPROM_Write(0x02, Posicion_S[2]);
                EEPROM_Write(0x03, Posicion_S[3]);
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                Enviar_Texto("Datos Guardados \n");
                F2 = 1;
                RBIF = 0;
            }
            if (!RB2)
            {
                Enviar_Texto("leyendo EEPROM \n");
                PWM_duty(1,map(EEPROM_Read(0x00),0,255,160,650));
                PWM_Mux_Channel_Select(0);
                __delay_ms(350);
                PWM_duty(1,map(EEPROM_Read(0x01),0,255,160,650));
                PWM_Mux_Channel_Select(1);
                __delay_ms(350);
                PWM_duty(1,map(EEPROM_Read(0x02),0,255,160,650));
                PWM_Mux_Channel_Select(2);
                __delay_ms(350);
                PWM_duty(1,map(EEPROM_Read(0x03),0,255,160,650));
                PWM_Mux_Channel_Select(3);
                __delay_ms(350);
                F2 = 1;
                RBIF = 0;
            }
        }

    }


    else if (PORTBbits.RB6 == 1)
    {
    if (F3 == 1)
    {
        Enviar_Texto("Menu UART \na. Recibir comandos, b. Salir modo Uart\n");
        F3 = 0;
    }

    Recibir_Texto(SEL,1);

            if (SEL[0] == 0x61)                   //En caso de ser "a" lee potenciometro
            {
                int numbers[4];
                Enviar_Texto("Ingrese Angulos: \n");
                for(int i = 0; i < 4; i++)
                {
                    char buffer[50];
                    Recibir_Texto(buffer, 3);

                    numbers[i] = string_to_int(buffer);

                    char numStr[12];
                    itoa(numStr, numbers[i], 10);

                    Enviar_Texto(numStr);
                    Enviar_Texto("\n");
                }

                PWM_duty(1,map(numbers[0],0,180,160,650));
                PWM_Mux_Channel_Select(0);
                __delay_ms(500);
                PWM_duty(1,map(numbers[1],0,180,160,650));
                PWM_Mux_Channel_Select(1);
                __delay_ms(500);
                PWM_duty(1,map(numbers[2],0,180,160,650));
                PWM_Mux_Channel_Select(2);
                __delay_ms(500);
                PWM_duty(1,map(numbers[3],0,180,160,650));
                PWM_Mux_Channel_Select(3);
                __delay_ms(500);

                Enviar_Texto("Listo\n");
                RCIF = 0;
                F3 = 1;
            }

            else if (SEL[0] == 0x62)
            {
            F1 = (F1 + 1) % 4;
            PORTB = (PORTB & 0x0F) | (1 << (F1 + 4));
            }


    }










}

//******************************************************************************
// Configuraciones
//******************************************************************************
void Setup(void)
{
    ANSEL  = 0x0F;  //Enciende primeros 4 canales del ADC
    ANSELH = 0x00;
    TRISA = 0x0F;   //Establece primeros dos bits de PORTA como entrada
    PORTA = 0;      //Limpia PORTA
    TRISB = 0X07;   //Establece PORTB como salida
    PORTB = 0X10;      //Limpia PORTB
    IOCB = 0X07;
    TRISC = 0;      //Establece PORTC como salida
    PORTC = 0;      //Limpia PORTC
    TRISD = 0;      //Establece PORTD como salida
    PORTD = 0;      //Limpia PORTD
    TRISE = 0;
    PORTE = 0x01;

    OPTION_REGbits.nRBPU = 0;

    OSCCONbits.SCS = 1;
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;



}

void Int_Enable(void)
{
    T0IF = 0;
    T0IE = 0;   //Habilitar interrupciones TMR0

    RBIF = 0;
    RBIE = 1;

    PEIE = 1;   //Habilitar interrupciones Perifericas
    GIE = 1;    //Habilitar interrupciones Globales
}


//******************************************************************************
// Subrutinas
//******************************************************************************
void ADC_Change(void)                           //Conmutar canal el cual se le hara lectura de ADC para ambos potenciometros
{
    if (ADCON0bits.GO)                          //Se chequea que no este ocurriendo una lectura de ADC
    {
        return;
    }
    else if (ADCF == 0)                  //En caso ADCF sea verdadero
    {
        ADC_Select(0);                          //Se selecciona el Canal 0 para la lectura de ADC
    }
    else if (ADCF == 1)
    {
        ADC_Select(1);                          //Se selecciona el Canal 1 para la lectura de ADC
    }
    else if (ADCF == 2)
    {
        ADC_Select(2);                           //Se selecciona el Canal 2 para la lectura de ADC
    }
        else if (ADCF == 3)
    {
        ADC_Select(3);                           //Se selecciona el Canal 3 para la lectura de ADC
    }
    while(ADCON0bits.GO);                       //Espera a terminar la conversion ADC
    ADCON0bits.GO = 1;                          //Inicia la conversion ADC
}


//******************************************************************************
// Main Loop
//******************************************************************************
void main(void)
{
    Setup();
    Int_Enable();

    PWM_config(1,4);
    PWM_Enable_Mux();

    ADC_Int(0);
    ADC_Isr_Enable();

    EUSART_Init();                      //Inicia y configura UART
    EUSART_Disable_TX_Isr();
    EUSART_Disable_RX_Isr();


    while(1)                                     //Loop principal
    {
        ADC_Change();                           //Llama a la funcion de conmutar el canal de ADC

    }
    return;
}
