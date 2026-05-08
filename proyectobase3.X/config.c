#include "xc.h"

void initPORTD(void) {
    // Descomentar y completar
    /*
    TRISD = ;
     */
}
void initADC(void) {
    // Descomentar y completar
    /*
    AD1CON2bits.CSCNA = ;
    AD1CSSL = ;
    AD1CSSH = ; 
    */
    AD1CON1bits.ADON = 1;
}
void initDMA(void) {
    // Descomentar y completar
    /*   
    // Buscar el IRQ correspondiente en el manual de referencia del DMA
    DMA0REQ = ;
    DMA0PAD = ;
    DMA0STA = ;
    DMA0CNT = ;
     */    
    IFS0bits.DMA0IF = 0;
    IEC0bits.DMA0IE = 1;
    DMA0CONbits.CHEN = 1;
}

void config(void) {
    initPORTD();
    initADC();
    initDMA();
}
