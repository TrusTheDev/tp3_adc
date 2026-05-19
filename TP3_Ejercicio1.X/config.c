#include "xc.h"

void initPuertos(void) {
    // Se configuran los puertos
    TRISD = 0xFFFF; // RD6 y RD7 como entrada
    TRISE = 0x0000; // Puerto E como salida
}

void initADC(void) {
    
    AD1PCFGL = 0xFFDB; // AN2 y AN5 como analógicos. El resto digitales
    
    // Configuraciones fijas
    AD1CON2 = 0x0000;
    AD1CON3 = 0x0002; // Se configura la velocidad de conversión 
    AD1CSSL = 0x0000; // Sin escaneo automático
    
    AD1CON1bits.ADON = 1; // Se prende el ADC
}

void config(void) {
    initPuertos();
    initADC();
}