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
int getState(int channel);
void printDelimiters();
int getCE(int channel);
double inputNumber();

int main()
{
    int end;
    do{
        int frequences[soundsParamsCount] = {784, 392, 440, 440, 784, 440, 493, 493};
        int delayParams[soundsParamsCount] = {200, 200, 200, 200, 200, 200, 200, 200};
	
        for(int i = 0; i < soundsParamsCount; i++)
        {
            generateSound(frequences[i], delayParams[i]);
        }
    
        outp(0x61, inp(0x61) & 0xFC);             // turn OFF dynamic
    
        delay(1000);

        printf("\n****Condition words****\n");
        printConditionWordInBinaryMode();
        printf("\n");

        printf("****Division coefficients****\n");
        printDelimiters();

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
        
        printf("\n\ninput 0 to exit or something else to continue...\n");
        end = (int)inputNumber();
    } while (end != 0);

	return 0;
}

/*
    Port 43 - управляющий
    Port 42 - канал 2, связан с динамиком
    Port 61 - включение динамика
    B6 - 10 11 011 0 - канал, read/write старший + младший байты, режим, формат(двоичный)
*/
void generateSound(int frequency, int delayParam)
{
	int divisionCoefficient;
	outp(0x43, 0xB6);                         

	divisionCoefficient = base / frequency;
	outp(0x42, divisionCoefficient % 256);      // low
	divisionCoefficient /= 256;                 // do smth for pause
	outp(0x42, divisionCoefficient);            // high

	outp(0x61, inp(0x61) | 3);                  // turn ON dymamic
	delay(delayParam);                          // wait  
    outp(0x61, inp(0x61) & 0xFC);               // turn OFF
}

/*
    Condition word:
    7 - OUT (condition of out)
    6 - флаг перегрузки констант
    4-5 - type of operation
    1-3 - mode
    0 - format
*/
void printConditionWordInBinaryMode()
{
    // 11(read);  1(don't save counter in buffer);   0(save condition word);
    // xxx(channel);   0(format)
	int state;

    for(int channel = 0; channel < 3; channel++ )
    {
        state = getState(channel);
        printState(state);
    }
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

//channel - 0, 1 or 2 only
int getState(int channel)
{// 1110 0010, 1110 0100, 1110 1000
	outp(0x43, 0xE0 + (2 << channel));			// 11(RBC mode: read channel mode) 1(not save CE - current state of counter) 0(read value of channel) number of channel 0
	return inp(0x40 + channel);
}

void printRandomNumbers(long max, int countOfNumbers)
{
	int delimiter;
    outp(0x43, 0xB4);                           //10 (channel 2) 11(RW lower, that higher) 010(mode 2: with autoloading) 0 (binary)
    
    // Load counter register of timer
	outp(0x42, max % 0x100);                    // at the begining low bytes    
    outp(0x42, max / 0x100);                    // then high bytes
    
    // enable only channel
	delimiter = inp(0x61);     
    outp(0x61, delimiter | 0x01);
    
	for(int i = 0; i < countOfNumbers; i++)
    {
	    delimiter = getCE(2);
	    printf("%d; ", delimiter);
	}
}

void printDelimiters()
{
	long kd, kdHigh, kdLow, kdMax = 0;
    const long CYCLE_COUNT = 47000;             // to find max delimiter
	for(int k=0; k < 3; k++){
        for (long i = 0; i<CYCLE_COUNT; i++)
	    {
           outp(0x43, 0x00 + (0x40 * k));        
           kdLow = inp(0x40 + k);               // load low
           kdHigh = inp(0x40 + k);              // load high
           kd = kdHigh * 256 + kdLow;
           if (kd > kdMax) kdMax = kd;
	    }
	    printf("%hx\n", kdMax);
	    kdMax=0;
    }
}

int getCE(int channel)
{
	int state, delimiter, port = 0x40;
	state = getState(channel);
    // select a channel
	outp(0x43, (state & 0x0F) | (channel << 6));			// (state & 0x0F) => SC (channel number) = 0, RW = 0 (get CE); than add channel number
	state = inp(port + channel);                            // take low bytes
	delimiter = inp(port + channel);                        // take high bytes
	delimiter <<= 8;                                           
	delimiter += state;
	return delimiter;
}

double inputNumber()
{
	int temp;
	double number;
	do {
		rewind(stdin);
		temp = scanf("%lf", &number);
	} while (temp == 0 || number < 0 || number > 32678);
	return number;
}
