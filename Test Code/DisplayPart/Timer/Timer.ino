/*
* Atmage328p Timer Test
* Interrupt Interval: 1/30/8/ = 0.00416 s = 4.16 ms
* Oscillation Period: 1/(16 x 10^6) = 0.0000000625 s = 0.0000625 ms
* Timer Comparison Value:
* -Prescalar Value  :       1      8       64     256    1024
* -Comparison Value :     66666   8333    1042    130     16
* Timer Mode: CTC
* -WGM12  -WGM11  -WGM10
*   1       0       0
*/
#include "IntConfig.h"

int counter = 0;

void TimerInit()
{
    /*
    * Initiate the timer for a fix interval
    */
    TCCR1A = 0x00;
    TCCR1B = 0x00;
    TCCR1B |= (1 << WGM12) | (CS11 << 1);
    OCR1A = 8333;
}

void setup(){
    Global_IntInit();
    T1_CompareA_IntInit();
    TimerInit();    
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
}

void loop(){
}


ISR(TIMER1_COMPA_vect)
{
    counter++;
    if (counter == 4)
    {
        counter = 0;
        PORTD = (~PORTD) & (1 << PD2); 
    }
}