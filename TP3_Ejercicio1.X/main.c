/*
 * File:   main.c
 * Author: Luciano Serruya Aloisi
 *
 * Created on May 14, 2019, 6:27 PM
 */

#include "xc.h"
#include "config.h"

#define TAM_BUFFER 8

int bufferRD6[TAM_BUFFER];
unsigned int bufferRD7[TAM_BUFFER];
int indiceRD6 = 0;
int indiceRD7 = 0;
int contador_ceros = 0;
int valor_convertido;

int main(void) {
    config();
    while(1) {
        
        // Si se aprieta el pulsador de RD6
        if(PORTDbits.RD6 == 1){
            
            // Configuración ADC para RD6
            AD1CON1bits.ADON = 0; // Se apaga para configurarlo
            AD1CHS0bits.CH0SA = 2; // Canal AN2
            AD1CON1bits.AD12B = 1; // 12 bits
            AD1CON1bits.FORM = 1; // Entero signado
            AD1CON1bits.ADON = 1; //Se vuelve a prender
            
            AD1CON1bits.SAMP = 1;  // Empieza el muestreo
            for(int i = 0; i < 1000; i++);
            AD1CON1bits.SAMP = 0; // Empieza la conversión
            
            while(!AD1CON1bits.DONE); // Polling hasta que termine la conversión
            
            // Lectura y guardado en buffer circular
            valor_convertido = ADC1BUF0;
            bufferRD6[indiceRD6] = valor_convertido;
            indiceRD6++;
            if(indiceRD6 == TAM_BUFFER){
                indiceRD6 = 0;
            }
            
            // Lógica del contador de ceros
            if(valor_convertido == 0xF800){
                contador_ceros++;
                PORTE = contador_ceros;
            }
        }
        
        // Si se aprieta el pulsador de RD7
        if(PORTDbits.RD7 == 1){
            
            // Configuración ADC para RD7
            AD1CON1bits.ADON = 0; // Se apaga para configurarlo
            AD1CHS0bits.CH0SA = 5; // Canal AN5
            AD1CON1bits.AD12B = 0; // 10 bits
            AD1CON1bits.FORM = 0; // Entero no signado
            AD1CON1bits.ADON = 1; //Se vuelve a prender
            
            AD1CON1bits.SAMP = 1;  // Empieza el muestreo
            for(int i = 0; i < 1000; i++);
            AD1CON1bits.SAMP = 0; // Empieza la conversión
            
            while(!AD1CON1bits.DONE); // Polling hasta que termine la conversión
            
            // Lectura y guardado en buffer circular
            valor_convertido = ADC1BUF0;
            bufferRD7[indiceRD7] = valor_convertido;
            indiceRD7++;
            if(indiceRD7 == TAM_BUFFER){
                indiceRD7 = 0;
            }
            
            // Lógica del contador de ceros
            if(valor_convertido == 0){
                contador_ceros++;
                PORTE = contador_ceros;
            }
        }
    }
    return 0;
}