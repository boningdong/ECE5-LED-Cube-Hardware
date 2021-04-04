/*
* Brightness Control
* Port Used: Timer_2 - OC2A
* PWM Frequency = 16M / (N * 256)
* -N is prescaler 
* 
*/
int SetStatus = 0;
void DimCtrlInit()
{
    OCR2A = 128;
    TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B |= (1 << WGM22) | (1 << CS21);
}

void setup()
{

}

void loop()
{
    if (SetStatus == 0)
    {
        SetStatus = 1;
        DDRB |= (1 << DDB3);
        DimCtrlInit();
    }
}
