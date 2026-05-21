/*
 * File:   main.c
 * Author: Luciano Serruya Aloisi
 *
 * Created on May 14, 2019, 6:27 PM
 */


#include "xc.h"
#include "config.h"

volatile int temperaturas[6] __attribute__((space(dma))); //arreglo especial 

void ResetCommand() {
    PORTD = 0x0000;
}

void up() {
PORTEbits.RE0 = 1;
}

void down() {
    PORTEbits.RE1 = 1;
}

void hold() {
PORTEbits.RE2 = 1;
}

void release() {
    PORTEbits.RE3 = 1;
}

int main(void) {
    config();
    while (1) {
        /*
         * Agregar la lógica necesaria
         * Agregar las variables que considere necesarias
         */
        PORTD = 0x0000; //Reinicio los comandos
        switch (PORTD) {
            case 1:
                up();
                break;
            case 2:
                down();
                break;

            case 3:
                hold();
                break;

            case 4:
                release();
                break;
        }
    }
    return 0;
}
