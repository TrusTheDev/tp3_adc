/*
 * File:   main.c
 * Author: Marcelo Gómez
 *
 * En este ejemplo se toman continuamente los valores de AN2 utilizando
 * el ADC2 y el canal DMA3.
 * El programa principal está continuamente sacando el valor de la suma
 * del buffer de DMA por el PORTD.
 * 
 * Created on May 10, 2020, 10:57 AM
 */
#include <p33FJ256GP710A.h>
#include <stdio.h>
#include "config.h"

int SumaValores;
extern int BufferA[5];

void __attribute__((interrupt, auto_psv)) _DMA3Interrupt(void)
{
    int i;
    
    SumaValores = 0;
    for(i = 0; i < 5; ++i)
        SumaValores += BufferA[i];
    
    IFS2bits.DMA3IF = 0;
}

int main(void)
{
    initDMA3();
    initADC2();

    TRISD = 0;  // PORTD de salida
    
    while(1)
    {
        PORTD = SumaValores;
    }
}