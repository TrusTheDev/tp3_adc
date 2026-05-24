#include "xc.h"

void initPORTDE(void) {
    AD1PCFGH = 0xFFFF;
    AD1PCFGL = 0xFFFF;
    
    TRISD = 0xFFFF; //Configuro TRISD como entrada para controlar al robot
    TRISE = 0x0000; //Configuro como salida para mostrar el estado del robot
}
void initADC(void) {
    AD1PCFGL = 0xFFFC; // AN0 y AN1 como analógicos. El resto digitales

    // Configuraciones fijas
    AD1CON1bits.SSRC = 7; // Arrancar la conversion al final del sampling
    AD1CON1bits.ASAM = 1; // ADC Sample Control: Sampling begins immediately after conversion
        AD1CON1bits.AD12B = 0; // 10 bits
    AD1CON1bits.FORM = 0; // Entero no signado

    AD1CON2bits.CSCNA = 1;
    AD1CON2bits.SMPI = 1; //Interrupción/evento cada 2 conversiones ADC en teoria
    
    
    AD1CON3bits.ADCS = 9; 
    AD1CON3bits.SAMC = 4; // 4 TAD
    AD1CSSL = 0x0003; // Escaneo consecutivo AN0 - AN1
    
}
extern unsigned int temperaturas[6] __attribute__((space(dma)));
void __attribute__((interrupt, auto_psv)) _DMA0Interrupt(void) {
    /* Rutina de atención para la interrupción del DMA */
    LATE = 0x30;
    IFS0bits.DMA0IF = 0;
}

void initDMA(void) {
    DMA0REQ = 13; //Seleccionado ADC1 como  la fuente de interrupcion
    DMA0PAD = (volatile unsigned int) &ADC1BUF0; // DMA apuntando a ADC1BUF0
    DMA0STA = __builtin_dmaoffset(temperaturas); //Le dice desde donde empieza a leer;
    DMA0CNT = 5;
 
    IFS0bits.DMA0IF = 0; // Clear DMA Interrupt Flag
    IEC0bits.DMA0IE = 1; // Enable DMA interrupt
    DMA0CONbits.CHEN = 1; // Enable DMA Channel
}

void config(void) {
    initPORTDE();
    initDMA();
    initADC();
    AD1CON1bits.ADON = 1; //Prendo el ADC
}
