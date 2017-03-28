#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>

// 23.	F(x) = x^2 – sin (sqrt (x)), x >= 0

double inputNumber();
double function_c(double a, double b, double step);
double function_asm(double a, double b, double step);

int main() 
{
	int flag = 1;
	do {
		printf("Hello, happy user! Enter interval values a, b, step to calculate f(x) for each value in this interval! ");
		double a = 0, b = 0, step = 0;

		printf("\nInput a - begin of interval: ");
		do {
			a = inputNumber();
		} while (a < 0);

		printf("Input b - end of interval: ");
		do {
			b = inputNumber();
		} while (b < 0 || b < a);

		printf("Input step: ");
		do {
			step = inputNumber();
		} while (step <= 0);

		double result_c = function_c(a, b, step);
		double result_asm = function_asm(a, b, step);

		printf("\nLast results\n");
		printf("\nresult in C language: %lf", result_c);
		printf("\nresult in assembler language: %lf", result_asm);

		printf("\nEnter 0 to exit or something else to continue: ");
		flag = inputNumber();
		system("cls");
	} while (flag != 0);
	return 0;
}

double function_c(double a, double b, double step)
{
	clock_t time = clock();
	double result;
	for (; a <= b; a += step) {
		result = pow(a, 2) - sin(sqrt(a));
	}
	printf("\nCalculating time in C language: %d", clock() - time);
	return result;
}

double function_asm(double a, double b, double step)
{
	clock_t time = clock();
	double result = 0;
	_asm finit
	for (; a <= b; a += step) {
		_asm {
			FLD a
			FLD a
			FMUL
			FLD a
			FSQRT
			FSIN
			FSUB
			FSTP result
		}
		_asm fwait
	}
	printf("\nCalculating time in assembler language: %d", clock() - time);
	return result;
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