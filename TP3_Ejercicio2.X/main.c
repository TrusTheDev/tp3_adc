/*
 * File:   main.c
 * Author: Luciano Serruya Aloisi
 *
 * Created on May 14, 2019, 6:27 PM
 */


#include "xc.h"
#include "config.h"

volatile unsigned int temperaturas[6] __attribute__((space(dma))); //arreglo especial 
int aux;
int cont;

void up() {
PORTEbits.RE0 = 1;
//Analizo la muestra

}

void down() {
    PORTEbits.RE4 = 1;
    PORTEbits.RE1 = 1;
}

void hold() {
PORTEbits.RE5 = 1;
PORTEbits.RE2 = 1;

    if (cont > 6) {
        cont = 0;
    }
    if (PORTEbits.RE1) {
        aux = temperaturas[cont]; //tomo la muestra
        temperaturas[cont] = 0; //elimino la muestra del arreglo
        cont++;
    }
}

void release() {
    PORTEbits.RE3 = 1;
    if(PORTEbits.RE1){
        if(cont > 6){
            temperaturas[cont-1] = aux;
        }
        else {
            temperaturas[cont] = aux;
        }
    }
    else {
        aux = 0;
    }
}

int main(void) {
    config();
    while (1) {
        /*
         * Agregar la lógica necesaria
         * Agregar las variables que considere necesarias
         */
        PORTE = 0x0000; //Reinicio los comandos
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
