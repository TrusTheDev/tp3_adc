/*
 * File:   config.c
 * Author: marcelo
 *
 * Created on 10 de mayo de 2020, 11:09
 */

#include "xc.h"

unsigned int BufferA[5] __attribute__((space(dma)));

void initDMA3(void)
{
    DMA3REQbits.IRQSEL = 21;
    DMA3PAD = (unsigned int) &ADC2BUF0;
    DMA3STA = __builtin_dmaoffset(BufferA);;
    DMA3CNT = 4;
  
    IFS2bits.DMA3IF = 0;
    IEC2bits.DMA3IE = 1;
    DMA3CONbits.CHEN = 1;
}

void initADC2(void)
{
    AD2PCFGL = 0xFFFB;
    AD2CON1bits.SSRC = 7;   // Espera un tiempo y pasa de sampling a conversion
    AD2CON1bits.AD12B = 1;  // Convertir a 12 bits
    AD2CON1bits.ASAM = 1;   // El sampling comienza automáticamente después de
                            // la conversión anterior
    AD2CHS0 = 0x0002;

    AD2CSSL = 0;
    AD2CON3 = 0x3F; // Tad = internal 64 Tcy
    AD2CON2 = 0;

    IFS1bits.AD2IF = 0;
    //IEC1bits.AD2IE = 1;   // NO se debe activar la int del ADC cuando
                            // lo usamos con el DMA

    AD2CON1bits.ADON = 1;
}