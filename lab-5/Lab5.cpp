#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <windows.h>

struct VIDEO
{
	unsigned char symbol;
	unsigned char attributes;
};

void showTime();
void setTime();
void setAlarm();
void printMsg(char* str, int numbSymb, int offset);
void setSleep();
int decimalToBcd(int decimalNumber);
void showCommands();

void interrupt (*alarmH) (...);
void interrupt newAlarmH(...)
{
	printMsg("Hey, Wake up!", 13, 20);
	setvect(0x4A, alarmH);
	alarmH(); 
}

unsigned int millis = 0;
void interrupt (*rtcH) (...);
void interrupt newRtcH(...)
{
	millis++;
	rtcH();
}

int main()
{	
	while(1)
	{ 
		system("cls");
			
		showTime();
		showCommands();
		
		printf(">> ");
			
		switch(getch())
		{
			case '0': return 0;
			case '1': setTime(); break;
			case '2': setAlarm(); break;	
			case '3': setSleep(); break;
		}
	}
}

void showTime()
{
	outp(0x70, 0x04); // регистр часов
	printf("%02hx:", inp(0x71));
	outp(0x70, 0x02); // регистр минут
	printf("%02hx:", inp(0x71));
	outp(0x70, 0x00); // регистр секунд
	printf("%02hx   ", inp(0x71));
	outp(0x70, 0x07); // регистр дня месяца
	printf("%02hx/", inp(0x71));
	outp(0x70, 0x08); // регистр месяца
	printf("%02hx/", inp(0x71));
	outp(0x70, 0x09); // регистр года
	printf("%02hx\n", inp(0x71));
	
}

int decimalToBcd (int decimalNumber)              
{
	return ((decimalNumber / 10 * 16) + (decimalNumber % 10));
}

void setTime()
{
	int hours = -1, minutes = -1, seconds = -1;
	int	weekDay = -1, monthDay = -1, month = -1, year = -1;
    
    int const waitingCounter = 5000;
	
	system("cls");
	printf("Curent time: ");
	showTime();
	
	printf("New hours: ");
	while(!scanf("%d", &hours) || hours < 0 || hours > 24)
	{
		printf("Input error, try again\n");
		fflush(stdin);
	}
	
	printf("New minutes: ");
	while(!scanf("%d", &minutes) || minutes < 0 || minutes > 59)
	{
		printf("Input error, try again\n");
		fflush(stdin);
	}
	
	printf("New seconds: ");
	while(!scanf("%d", &seconds) || seconds < 0 || seconds > 59)
	{
		printf("Input error, try again\n");
		fflush(stdin);
	}
	
	printf("New day of week: ");
	while(!scanf("%d", &weekDay) || weekDay < 0 || weekDay > 7)
	{
		printf("Input error, try again\n");
		fflush(stdin);
	}
	
	printf("New day of month: ");
	while(!scanf("%d", &monthDay) || monthDay < 0 || monthDay > 31)
	{
		printf("Input error, try again\n");
		fflush(stdin);
	}
	
	printf("New month: ");
	while(!scanf("%d", &month) || month < 0 || month > 12)
	{
		printf("Input error, try again\n");
		fflush(stdin);
	}
	
	printf("New year: ");
	while(!scanf("%d", &year) || year < 0)
	{
		printf("Input error, try again\n");
		fflush(stdin);
	}
	
	outp(0x70, 0xA); // A регистр состояния 7 бит -> 1 - идёт обновление времени, 0 - доступ (обнвление) разрешен 
	
	int iter = 0;
	while (inp(0x71) > 127 && iter < waitingCounter) iter++;
	
	if(iter >= waitingCounter)
	{
		printf("Sorry, we have some errors");
		return;
	}
	
	outp(0x70, 0xB); // B регистр состояния - 7 бит запрещение обновления часов -> 1 - идёт установка часов, 0 - обновление разрешено
	outp(0x71, inp(0x71) | 0x80); //10000000b 							

	outp(0x70, 0x00);															
	outp(0x71, decimalToBcd(seconds));
	outp(0x70, 0x02);														
	outp(0x71, decimalToBcd(minutes));
	outp(0x70, 0x04);													
	outp(0x71, decimalToBcd(hours));
	outp(0x70, 0x06);
	outp(0x71, decimalToBcd(weekDay));
	outp(0x70, 0x07);
	outp(0x71, decimalToBcd(monthDay));
	outp(0x70, 0x08);
	outp(0x71, decimalToBcd(month));
	outp(0x70, 0x09);
	outp(0x71, decimalToBcd(year));

	outp(0x70, 0xB);
	outp(0x71, inp(0x71) & 0x7F); //01111111 - разрешение обновления часов
}
	
void setAlarm()
{
	int hours = -1, minutes = -1, seconds = -1;
	
	system("cls");
	printf("Curent time is ");
	showTime();
	
	printf("Alarm hours: ");
	while(!scanf("%d", &hours) || hours < 0 || hours > 24)
	{
		printf("Input error, try again\n");
		fflush(stdin);
	}
	
	printf("Alarm minutes: ");
	while(!scanf("%d", &minutes) || minutes < 0 || minutes > 59)
	{
		printf("Input error, try again\n");
		fflush(stdin);
	}
	
	printf("Alarm seconds: ");
	while(!scanf("%d", &seconds) || seconds < 0 || seconds > 59)
	{
		printf("Input error, try again\n");
		fflush(stdin);
	}								

	outp(0x70, 0x01); //регистр секунд будильника														
	outp(0x71, decimalToBcd(seconds));
	outp(0x70, 0x03); //регистр минут будильника															
	outp(0x71, decimalToBcd(minutes));
	outp(0x70, 0x05); //регистр часов будильника														
	outp(0x71, decimalToBcd(hours));
	
	outp(0x70, 0xB); // B регистр состояния - 5 бит разрешение прерывания будильника, 1 - разрешено, 0 - запрещено
	outp(0x71, (inp(0x71) | 0x20)); //00100000b

	_disable();
	
	alarmH = getvect(0x4A);												
	setvect(0x4A, newAlarmH);
	
	_enable();
		
	outp(0xA1, (inp(0xA1) & 0xFE));	//11111110 Размаскирование линии сигнала запроса от ЧРВ
}

void printMsg(char* str, int numbSymb, int offset)
{
	VIDEO far* videobuffer = (VIDEO far*)MK_FP(0xB800, 0);
	videobuffer += offset;

	for( int i = 0; i < numbSymb ; i++)
	{
		videobuffer->symbol = *(str + i);
		videobuffer->attributes = 0x02;
		videobuffer++;
	}
}

void setSleep()
{
	long sleepTime;
	
	printf("Enter sleep time in ms: ");
	while(!scanf("%ld", &sleepTime) || sleepTime < 0 || sleepTime > 65535)
	{
		printf("Input error, try again\n");
		fflush(stdin);
	}
	
	_disable();
	
	rtcH = getvect(0x70);
	setvect(0x70, newRtcH);
	
	_enable();
	
	outp(0xA1, (inp(0xA1) & 0xFE)); //11111110 - младший бит в 0 (Размаскирование линии сигнала запроса от ЧРВ)
	
	outp(0x70, 0xB); // B регистр состояния - 6 бит разрешение периодических прерываний IRQ8, 1 - разрешено, 0 - запрещено
	outp(0x71, inp(0x71) | 0x40); //01000000b - включение периодических прерываний IRQ8 
	
	millis = 0;
	
	system("cls");
	showTime();
	printf("Sleep %u ms...", sleepTime);
	
	while (millis <= sleepTime);
	
	_disable();

	setvect(0x70, rtcH);
	
	_enable();
}

void showCommands()
{
    printf("0 - Exit\n");
    printf("1 - Set new time\n");
    printf("2 - Set alarm\n");
    printf("3 - Delay in millis\n");
}