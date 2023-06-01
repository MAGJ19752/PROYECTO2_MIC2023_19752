/*
Archivo:        Proyecto2_2023
Dispositivo:    PIC16F887
Autor:		Mariel González Juárez (19752)
Compilador:     XC8, MPLABX 5.40
Programa:       Garra mecánica
*/
#ifndef __PWM__

#include <xc.h>

void PWM_config(char canal, int periodo); //n�mero del canal PWM, valor del per�odo

void PWM_duty(char canal, unsigned short duty); //establece el ciclo del trabajo del pwm

void PWM_Enable_Mux(void); //habilita el mux

void PWM_Disable_Mux(void); //dehabilita el mux

void PWM_Mux_Channel_Select(int channel); //selecciona el canal del mux

#endif /* __PWM__ */