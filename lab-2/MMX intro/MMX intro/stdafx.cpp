// stdafx.cpp : source file that includes just the standard includes
// MMX intro.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

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