/*
 * File:   main.c
 * Author: Luciano Serruya Aloisi
 *
 * Created on May 14, 2019, 6:27 PM
 */

#include "xc.h"
#include "config.h"

volatile unsigned int temperaturas[6] __attribute__((space(dma)));

void __attribute__((interrupt, auto_psv)) _DMA0Interrupt(void) {
    /* Rutina de atención para la interrupción del DMA */
    LATE = 0x30;
    IFS0bits.DMA0IF = 0;
}

int main(void) {
    config();
    while(1) {
        if(PORTDbits.RD0 == 1){
            // UP: tipo 1, pin 0
            LATE = 0x11;
        }
        else if(PORTDbits.RD1 == 1){
            // DOWN: tipo 1, pin 1
            LATE = 0x12;
        }
        else if(PORTDbits.RD2 == 1){
            // HOLD: tipo 2, pin 2
            LATE = 0x24;
        }
        else if(PORTDbits.RD3 == 1){
            // RELEASE: tipo 2, pin 3
            LATE = 0x28;
        }
    }
    return 0;
}