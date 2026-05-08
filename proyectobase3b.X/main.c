#include <p33FJ256GP710A.h>
#include <stdio.h>

int ADCValue;
int finConversion;

void __attribute__((interrupt, auto_psv)) _ADC1Interrupt( void )
{
	ADCValue = ADC1BUF0;

	finConversion = 1;

	IFS0bits.AD1IF = 0;
}

int main(void)
{
AD1PCFGL = 0xFFFB;
AD1CON1bits.SSRC = 7;   // Espera un tiempo y pasa de sampling a conversion

AD1CHS0 = 0x0002;

AD1CSSL = 0;
AD1CON3 = 0x3F; // Tad = internal 64 Tcy
AD1CON2 = 0;

IFS0bits.AD1IF = 0;

IEC0bits.AD1IE = 1;

AD1CON1bits.ADON = 1;

finConversion = 0;

while(1)
{
  AD1CON1bits.SAMP = 1;
  // delay(1);              // Ahora no es necesario porque
  //AD1CON1bits.SAMP = 0;   // pasa automaticamente a conversion
  while (!finConversion)
      ;
  finConversion = 0;
  
  // Hacer algo con el valor en la variable ADCValue
  ADCValue = ADCValue / 2;
}
}