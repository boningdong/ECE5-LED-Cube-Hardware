//Micro-controller Atmega 328P
void LayerDisplay(unsigned char);
void LayerDisplayInit();
void ShiftClk();
void LatchClk();
void DelayClock();

int SHCP = 6; 	//PD6
int STCP = 5; 	//PD5
int SDIN = 4; 	//PD4
int RST = 7;	//PD7
int key = 2;	//PD2
int PWM = 11;

int layer = 0;
int delaytime = 50;

unsigned char layer_data [8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char disp_data [8][8] = {	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
									{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, 
									{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, 
									{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, 
									{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, 
									{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, 
									{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, 
									{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  };

void setup() 
{
  // put your setup code here, to run once:
  LayerDisplayInit();
  LayerChooseInit();
  LayerDisplay(layer_data);
  LayerChoose(layer);
  pinMode(PWM, OUTPUT);
  digitalWrite(PWM, LOW);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  
	layer ++;
	if (layer <= 7)
	{
		LayerChoose(layer);
		delay(delaytime);
	}
	else
	{
		layer = 0;
		LayerChoose(layer);
		delay(delaytime);
		delaytime -= 2;
	}
	
	if (delaytime <=15)
	{
		delaytime = 15;
	}
	
}

/*	Function: Layer-data controll and display
 *	Details: The following part is for displaying each layer 
 *	Note: The byte sequence, data_array [0] = colum [8] 
 *						 	 data_array [1] = colum [7]
 *							 data_array [x] = colum [8-x]
 *		  Each data_array has size of a byte: xxxx xxxx
 *		  Each bit is 1 or 0. 1 means turn off; 0 means turn on.
 */

 
void LayerDisplayInit()
{
	DDRD |= (1 << SHCP) | (1 << STCP) | (1 << SDIN) | (1 << RST);
	PORTD |= (1 << RST);
}

void LayerDisplay(unsigned char layer_data[])
{
	/*
	* Data Type:
	* -layer_data should be an array including 8 char type data.
	*/
    char i, y;
    for (i = 0; i <= 7; i++)
    {
    	for (y = 0; y <= 7; y++)
		{
          	PORTD &= (~(0x01 << 4));   //PORTD Register
          	PORTD |= ((((0x01 << y) & layer_data[i]) >> y) << 4);
			ShiftClk();
        }
		LatchClk();
    }
}

/*
//Need to be tested
void SetLED_DispData(char coordinate[])
{
	unsigned char x = 0, y = 1, z = 2;
	disp_data[ coordinate[z] ][ coordinate[y] ] &= ~( 1 << coordinate[x] );
}

//Need to be tested
void ResetLED_DispData()
{
	int i = 0;
	for (; i < 64; i ++)
	{
		disp_data[i] = 0x00;
	}
}
*/

void ShiftClk()
{
    PORTD |= (0x01 << SHCP);
	DelayClock();
    PORTD &= ~(0x01 << SHCP);
}

void LatchClk()
{
	PORTD |= (0x01 << STCP);
    DelayClock();
    PORTD &= ~(0x01 << STCP);
}

/*	Function: Layer Enable control
 *	Details: The following part is for controlling which layer will be turned on
 *	Note: When send the number of layer, the decimal number will be stored in register as binary format.
 *		  When layer = 0. PORTC = 0000 0000, which means A0=0, A1=0, A2=0 on 74HC138, then Layer-0 will be turned on
 *		  When layer = 1. PORTC = 0000 0000, which means A0=1, A1=0, A2=0 on 74HC138, then Layer-1 will be turned on
 *		  When layer = x. PORTC = 0000 0xxx, which means A0=1/0, A1=1/0, A2=1/0 on 74HC138, then Layer-x will be turned on
 */
void LayerChooseInit()
{
	DDRC |= (1 << DDC0) | (1 << DDC1) | (1 << DDC2);	//Set PC0 (A0), PC1 (A1), PC2 (A2) to be output mode
	PORTC = 0x00;
}

void LayerChoose(char layer)
{
	PORTC = layer; //layer should be between 0 - 7
}

void DelayClock()
{
   	char i = 0;
   	for (; i < 100; i++);
}