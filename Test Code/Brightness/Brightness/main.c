/*
 * Brightness.c
 *
 * Created: 2/19/2017 4:53:23 PM
 * Author : Boning-Dell
 */ 

#include <avr/io.h>
void DimCrtlInit();

int main(void)
{
    /* Replace with your application code */
	DDRB |= (1 << DDB3);
	DimCrtlInit();
	while (1) 
    {
	}
}

void DimCrtlInit()
{
	OCR2A = 128;
	TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
	TCCR2B |= (1 << WGM22) | (1 << CS21);
}
