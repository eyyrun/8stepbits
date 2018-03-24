/*
 * main.c
 *
 *  Created on: 28. feb. 2018
 *      Author: eyrunengilbertsdottir
 */

// naestu skref:
// er ad nota HW7 og athuga hvernig thad virkar ad vera ad lesa af
// fleirum en einum analog pinna i einu
//
// finna sidan utur thvi hvernig eg set inn gildi (bit eda hex?) inni compare
// -- henda inn matlab listum af gildum
//
// athuga hvad gylfi er ad nota til ad fa fjarlaegdargildin a sensorinn
// --> baeta vid mitt verkefni?
// henda i analog LPF
//
// byrja ad tekka hvad thu tharft ad maela, fa results inn i skyrslu



#include <avr/io.h>
#include "waveformGenerator.h"

void mydelay(long int k)
{
	long int i;
	for (i = 0; i < k; i++)
	{
		asm("nop"); //no operation for one cycle
	}
}

void waveGen(unsigned int adc_value0, unsigned int adc_value1)
{
	// eg vil frekar koma rettum gildum inn i compA og geta tha eiginlega sleppt thessu
	// -- hvernig virkar tha ad gera dotid sem er utan um thetta?
	int i, period, cycles;
	period = 500000/ (adc_value0+1);
	cycles = (adc_value0 * adc_value1)/1000;

	for(i=0; i<= cycles; i++)
	{
		PORTB |= (1<<3);
		mydelay(period); //crest widens
		PORTB &= ~(1<<3);
		mydelay(period);   //trough shrinks
	}
}

void ADC_setup()
{
	ADMUX = (1 << REFS0);
	//ADCSRB untouched as it is default in free-running-mode after reset
	// power on ADC, activate free running mode, start converting, 128 prescaler (->125kHz)
	ADCSRA |= (1<<ADEN)|(1<<ADATE)|(1<<ADSC)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

int readADC0()
{
	ADC_setup();
	return ADCW;
}

int readADC1()
{
	ADMUX |= (1 << REFS0)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(1<<MUX0);
	return ADCW;
}

int main()
{
	DDRB = 0b11111000; //pin 8 - 10 inputs, 11-13 outputs
	//set up ADC
	ADC_setup();

	int sine[630] = {128, 129, 131, 132, 133, 134, 136, 137, 138, 139, 141, 142, 143, 144, 146, 147, 148, 149, 151, 152, 153, 154, 156, 157, 158, 159, 161, 162, 163, 164, 166, 167, 168, 169, 170, 172, 173, 174, 175, 176, 177, 179, 180, 181, 182, 183, 184, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 215, 216, 217, 218, 219, 220, 221, 222, 223, 223, 224, 225, 226, 227, 227, 228, 229, 230, 231, 231, 232, 233, 233, 234, 235, 236, 236, 237, 238, 238, 239, 239, 240, 241, 241, 242, 242, 243, 243, 244, 244, 245, 245, 246, 246, 247, 247, 248, 248, 249, 249, 249, 250, 250, 250, 251, 251, 251, 252, 252, 252, 252, 253, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 254, 254, 254, 254, 253, 253, 253, 253, 252, 252, 252, 252, 251, 251, 251, 250, 250, 250, 249, 249, 249, 248, 248, 247, 247, 246, 246, 246, 245, 245, 244, 243, 243, 242, 242, 241, 241, 240, 240, 239, 238, 238, 237, 236, 236, 235, 234, 234, 233, 232, 231, 231, 230, 229, 228, 228, 227, 226, 225, 224, 224, 223, 222, 221, 220, 219, 218, 217, 217, 216, 215, 214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 193, 192, 191, 190, 189, 188, 187, 186, 185, 183, 182, 181, 180, 179, 178, 176, 175, 174, 173, 172, 171, 169, 168, 167, 166, 165, 163, 162, 161, 160, 158, 157, 156, 155, 153, 152, 151, 150, 148, 147, 146, 145, 143, 142, 141, 140, 138, 137, 136, 135, 133, 132, 131, 129, 128, 127, 126, 124, 123, 122, 121, 119, 118, 117, 116, 114, 113, 112, 110, 109, 108, 107, 105, 104, 103, 102, 100, 99, 98, 97, 96, 94, 93, 92, 91, 89, 88, 87, 86, 85, 83, 82, 81, 80, 79, 78, 76, 75, 74, 73, 72, 71, 70, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 34, 33, 32, 31, 30, 29, 29, 28, 27, 26, 26, 25, 24, 23, 23, 22, 21, 21, 20, 19, 19, 18, 17, 17, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9, 8, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9, 10, 10, 11, 11, 12, 12, 13, 14, 14, 15, 15, 16, 16, 17, 18, 18, 19, 20, 20, 21, 22, 22, 23, 24, 24, 25, 26, 27, 27, 28, 29, 30, 31, 31, 32, 33, 34, 35, 36, 37, 38, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 65, 66, 67, 68, 69, 70, 71, 72, 74, 75, 76, 77, 78, 79, 81, 82, 83, 84, 85, 86, 88, 89, 90, 91, 93, 94, 95, 96, 97, 99, 100, 101, 102, 104, 105, 106, 107, 109, 110, 111, 112, 114, 115, 116, 117, 119, 120, 121, 123, 124, 125, 126, 128};

	//int adc_value0;
	//int adc_value1;

	//for(int i=0; i<8; i++)
	//{
	while(1)
	{
		//adc_value0 = readADC(0);
		//adc_value0 = 512;
		//adc_value1 = readADC1();

		if(PINB & (1<<2)) //if on/off switch is ON
		{
			PORTB |= (1<<5);
			//waveGen(adc_value0, adc_value1);
			//void sineWave()
			//{
				int i = -1;
				while(1)
				{
					mydelay(10000);
					OCR0A = sine[nextValue(i)];
				}
			//}
		}
		else
			PORTB &= ~(1<<5);
	}

	//}


// helloooo
	return 0;
}
