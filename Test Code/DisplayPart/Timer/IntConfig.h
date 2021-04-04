void Global_IntInit();
void T1_CompareA_IntInit();
void T1_CompareA_IntOff();

void Global_IntInit()
{
    sei(); 
}

void T1_CompareA_IntInit()
{
    TIMSK1 |= (1 << OCIE1A);
}

void T1_CompareA_IntOff()
{
    TIMSK1 &= ~(1 << OCIE1A);
}