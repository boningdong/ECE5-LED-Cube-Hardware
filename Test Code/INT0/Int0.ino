#include <Arduino.h>

void InitComm();
void LEDInit();

void setup()
{
    InitComm();
    sei();
    LEDInit();
}
    
    

void loop()
{

}

void LEDInit()
{
    DDRB |= (1 << DDB5);
    PORTB |= (1 << PORTB5);
}

void InitComm()
{
    /*
    * Enable External Interrupt 0
    */
    DDRD &= ~(1 << DDD2); //Input Mode
    PORTD |= (1 << PD2); //Pull Up
    EICRA |= (1 << ISC01); //Falling Edge Trigger
    EIMSK |= (1 << INT0); //Interrupt 1 Enable
}

ISR(INT0_vect)
{
    PORTB ^= (1 << PORTB5);
    delay(100);
}