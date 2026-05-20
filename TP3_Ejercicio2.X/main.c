/*
 * File:   main.c
 * Author: Luciano Serruya Aloisi
 *
 * Created on May 14, 2019, 6:27 PM
 */


#include "xc.h"
#include "config.h"

volatile int temperaturas[6] __attribute__((space(dma))); //arreglo especial 

void up(){
    
}
void down(){
    
}
void hold() {
    
}
void release(){
    
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
