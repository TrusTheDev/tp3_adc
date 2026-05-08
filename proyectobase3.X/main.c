/*
 * File:   main.c
 * Author: Luciano Serruya Aloisi
 *
 * Created on May 14, 2019, 6:27 PM
 */


#include "xc.h"
#include "config.h"

void __attribute__((interrupt, auto_psv)) _DMA0Interrupt(void) {
    /* Rutina de atención para la interrupción del DMA */
    IFS0bits.DMA0IF = 0;
}


int main(void) {
    config();
    while(1) {
        /*
         * Agregar la lógica necesaria
         * Agregar las variables que considere necesarias
         */
    }
    return 0;
}
