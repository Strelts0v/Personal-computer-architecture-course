#include <dos.h>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>

unsigned int lightMusicFlag = 0;						//Переменная-сигнал о мигании
unsigned int loopFlag = 1;								//Переменная счетчик цикла
unsigned int tryCount = 2;								//Количество попыток для ошибки
int exitLabel = 0;										//Флаг для выхода
int keyFlag = 1;                                        //Флаг для нажатия/отжатия

void interrupt(*oldKeyboard)(...);						//Старое прерывание от клавиатуры(09h)
void interrupt newKeyboard(...)						    //Наш обработчик прерываний клавиатуры
{
	unsigned char pressedButton;						//Переменная контейнер для нажатой клавиши

	pressedButton = inp(0x60);							//Получаем символ из буфера клавиатуры
	if (pressedButton == 0x01)							//Если нажата клавиша Esc
	{
		exitLabel = 1;									//Сигнализируем о выходе
		return;
	}

	if (pressedButton == 0xFE && lightMusicFlag)		//Если в переменную передался сигнал об ошибке во время мигания
	{
		if (tryCount-- == 0)							//Проверяем количество попыток
		{
			printf("Try access later. \n");  			//Если истекли, значит регистр клавиатуры занят
			exitLabel = 1;								//Сигнализируем о выходе
		}
		loopFlag = 1;									//Если же нет то продолжаем цикл
	}
	else												//Если же ошибки нет
	{
		loopFlag = 0;									//Останавливаем цикл
		tryCount = 2;									//Возвращаем наши потраченные попытки
	}

    if(keyFlag == 1){
	    printf("%x\t", pressedButton);					//Выводим символы нажатия на экран
        keyFlag = 0;
    } else {
	    printf("%x\n", pressedButton);					//Выводим символы отжатия на экран
        keyFlag = 1;
    }
	outp(0x20, 0x20);									//Просто очистка
	outp(0xA0, 0x20);
}

void lightMusic(unsigned char lamp)					    //Функция светомузыки лампочек клавиатуры
{
	int timer = 30000;									//Интервал для проверки
    int const DELAY_VALUE = 200;
	loopFlag = 1;
	while (loopFlag)									//Пока не изменим переменную, крутим цикл проверки
	{
		while (timer-- > 0)								//Пока таймер больше 0
		{
			if ((inp(0x64) & 0x02) == 0x00)				//Проверяем, пуст ли наш буфер клавиатуры
			{
				break;								    //Если же он пуст, то выходим
			}
		}
		if (!timer)										//Если возникает ошибка
		{
			printf("Interval timer error.\n");
			disable();								    //Отключаем прерывания
			setvect(0x09, oldKeyboard);				    //Возвращаем старый обработчик клавиатуры
			enable();									//Разрешаем прерывания
			exit(1);							        //Выходим из программы
		}
		outp(0x60, 0xED);								//Если в итоге все хорошо, разрешаем мигать лампочкой
		delay(DELAY_VALUE);								//Задержка чтоб был видно мигание
	}
	timer = 30000;
	loopFlag = 1;
	while (loopFlag)								   //Второй цикл нужен не для инициализации, а уже для мигания
	{
		while (timer-- > 0){
			if ((inp(0x64) & 0x02) == 0x00){		   //Также проверяем буфер на пустоту
				break;
			}
		}
		if (!timer)
		{
			printf("Interval timer error.\n");		   //В случае ошибки сигнализируем
			disable();								   //Отключаем прерывания
			setvect(0x09, oldKeyboard);			       //Возвращаем старое прерывание клавиатуры
			enable();								   //Разрешаем прерывания
			exit(1);								   //Выходим из программы
		}
		outp(0x60, lamp);							   //Если все хорошо, то включаем ту лампочку, которая надо
		delay(DELAY_VALUE);							   //Задержка для наглядности
	}
}

int main()											
{
    int signalCount = 0;
    printf("Input count of signals: ");
    while(!scanf("%d", &signalCount) || signalCount < 1 || signalCount > 100)
	{
		printf("Input error, try again\n");
		fflush(stdin);
	}
	delay(1000);										//Делаем задержку
	disable();											//Отключаем прерывания

	oldKeyboard = getvect(0x09);						//Получаем старый обработчик прерывания клавиатуры
	setvect(0x09, newKeyboard);						    //И назначаем наш новый обработчик

	enable();											//Разрешаем прерывания
	lightMusicFlag = 1;										//Сигнализируем о том, что хотим мигать
	for(int j=0; j < signalCount; j++)								
	{
		lightMusic(0x04);								//Мигание Caps Lock
		lightMusic(0x00);								//Отключение
		lightMusic(0x02);								//Мигание Num Lock
	}
	
	lightMusicFlag = 0;									//Перестаем мигать

	while (!exitLabel);									//Висим бесконечно и отображаем нажатые символы

	disable();											//Перед выходом
	setvect(0x09, oldKeyboard);						    //Возвращаем наш старый обработчик прерывания
	enable();											//Разрешаем прерывания заново
	return 0;
}
