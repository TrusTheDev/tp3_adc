#include <p33FJ256GP710A.h>
int ADCValue;

int main(void)
{
AD1PCFGL = 0xFFFB;	// all PORTB = Digital; RB2 = analog
AD1CON1 = 0x0000;	// SAMP bit = 0 ends sampling ...
			// and starts converting

AD1CHS0 = 0x0002;	// Connect RB2/AN2 as CH0 input ..
			// in this example RB2/AN2 is the input

AD1CSSL = 0;
AD1CON3 = 0x0002;	// Manual Sample, Tad = internal 2 Tcy
AD1CON2 = 0;

AD1CON1bits.ADON = 1;	// turn ADC ON

while(1)			// repeat continuously
{
  AD1CON1bits.SAMP = 1;		// start sampling ...
  //DelayNmSec(100);			// for 100 mS
  AD1CON1bits.SAMP = 0;		// start Converting
  while (!AD1CON1bits.DONE);	// conversion done?
  ADCValue = ADC1BUF0;		// yes then get ADC value
}	// repeat
}