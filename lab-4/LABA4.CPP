#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define base 1193180          // basic frequency (system generator of pulses)
#define soundsParamsCount 8

void printConditionWordInBinaryMode();
void printState(int state);
void printRandomNumbers(long max, int countOfNumbers);
void generateSound(int frequency, int delayParam);
void printDivisionCoefficient();
double inputNumber();

int main()
{
    int frequences[soundsParamsCount] = {784, 392, 440, 440, 784, 440, 493, 493};
    int delayParams[soundsParamsCount] = {200, 200, 200, 200, 200, 200, 200, 200};
	
    int i;
    for(i = 0; i < soundsParamsCount; i++)
    {
        generateSound(frequences[i], delayParams[i]);
    }
    
    delay(1000);

    printf("\n****Condition words****\n");
	printConditionWordInBinaryMode();
	printf("\n");

    printf("****Division coefficients****\n");
	printDivisionCoefficient();

	long max;
    int countOfNumbers;
    printf("\nInput max random value: ");
	do{
        max = (long)inputNumber();
    } while (max <= 0);
    
    
    printf("Input how many you need to generate: ");
    do{
        countOfNumbers = (int)inputNumber();
    } while (countOfNumbers <= 0);
    
    printf("Generated numbers:\n");
	printRandomNumbers(max, countOfNumbers);

	return 0;
}

/*
    Port 43 - control
    Port 42 - channel 2, connected with dynamic
    Port 61 - turn ON dynamic
    B6 - 10 11 011 0 - channel, high & low bytes, mode, format(binary)
*/
void generateSound(int frequency, int delayParam)
{
	int divisionCoefficient;
	outp(0x43, 0xB6);                         //10 11 011 0

	divisionCoefficient = base / frequency;
	outp(0x42, divisionCoefficient % 256);    // Low
	divisionCoefficient /= 256;               // Do smth for pause
	outp(0x42, divisionCoefficient);          // High

	outp(0x61, inp(0x61) | 3);                // turn ON dymamic
	delay(delayParam);                        // wait  
	outp(0x61, inp(0x61) & 0xFC);             // turn OFF dynamic
}

/*
    Condition word:
    7 - OUT
    6 - counter readiness for reading
    4-5 - type of operation
    1-3 - mode
    0 - format
*/
void printConditionWordInBinaryMode()
{
    // 11(read);  1(don't save counter in buffer);   0(save condition word);
    // xxx(channel);   0(format)
	int state;

	outp(0x43, 0xE2);      // 1110 0010
	state = inp(0x40);
	printState(state);

	outp(0x43, 0xE4);      // 1110 0100
	state = inp(0x41);
	printState(state);

	outp(0x43, 0xE8);      // 1110 1000
	state = inp(0x42);
	printState(state);
}

void printState(int state)
{
	int i;
	char temp[8];
	for (i = 7; i >= 0; i--)
	{
		temp[i] = state % 2 + '0';
		state /= 2;
	}
	for (i = 0; i < 8; i++)
	{
		printf("%c", temp[i]);
	}
	printf("\n");
}

void printRandomNumbers(long max, int countOfNumbers)
{
	long divisionCoefficientLow, divisionCoefficientHigh, divisionCoefficientNew;
    outp(0x43, 0xB6); // 1011 0100
    // Load conter register of timer
	outp(0x42, max & 0x00ff);          // at the begining low bytes    
    outp(0x42, (max & 0xff00) >> 8);   // then high bytes
	outp(0x61, inp(0x61) | 0x01);      // enable work of channel
    int i = 0;
	for(i = 0; i < countOfNumbers; i++)
    {
        delay(i);
		outp(0x43, 0x86); // 1000 0110
		divisionCoefficientLow = inp(0x42);
		divisionCoefficientHigh = inp(0x42);
		divisionCoefficientNew = divisionCoefficientHigh * 256 + divisionCoefficientLow;
		printf("%ld\n", divisionCoefficientNew);
	}
	outp(0x61, inp(0x61) & 0xFC);      // disable work of channel
}

/*
    format for outp : KK 00 0000
*/
void printDivisionCoefficient()
{
	long divisionCoefficient, divisionCoefficientHigh, divisionCoefficientLow, divisionCoefficientMax = 0;

    // Channel 0
    for (long i = 0; i < 65535; i++)
    {
        outp(0x43, 0x00);       //00 00 0000
        divisionCoefficientLow = inp(0x40);
        divisionCoefficientHigh = inp(0x40);
        divisionCoefficient = divisionCoefficientHigh * 256 + divisionCoefficientLow;
        if (divisionCoefficient > divisionCoefficientMax) divisionCoefficientMax = divisionCoefficient;
    }
    printf("%hx\n", divisionCoefficientMax);
    
    // Channel 1
    divisionCoefficientMax = 0;
    for (i = 0; i < 65535; i++)
    {
        outp(0x43, 0x40);       // 01 00 0000
        divisionCoefficientLow = inp(0x41);
        divisionCoefficientHigh = inp(0x41);
        divisionCoefficient = divisionCoefficientHigh * 256 + divisionCoefficientLow;
        if (divisionCoefficient > divisionCoefficientMax) divisionCoefficientMax = divisionCoefficient;
    }
    printf("%hx\n", divisionCoefficientMax);
    
    // Channel 2
    divisionCoefficientMax = 0;
    for (i = 0; i < 65535; i++)
    {
        outp(0x43, 0x80);       //10 00 0000
        divisionCoefficientLow = inp(0x42);
        divisionCoefficientHigh = inp(0x42);
        divisionCoefficient = divisionCoefficientHigh * 256 + divisionCoefficientLow;
        if (divisionCoefficient > divisionCoefficientMax) divisionCoefficientMax = divisionCoefficient;
    }
    printf("%hx\n", divisionCoefficientMax);
			
}

double inputNumber()
{
	int temp;
	double number;
	do {
		rewind(stdin);
		temp = scanf("%lf", &number);
	} while (temp == 0 && number < 0);
	return number;
}
