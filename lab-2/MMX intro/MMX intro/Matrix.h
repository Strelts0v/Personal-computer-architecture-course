#pragma once

#include "stdafx.h"

class Matrix
{
private:

	int** matrix;

	int columnsCount;

	int stringsCount;

public:

	Matrix(int stringsCount, int columnsCount);

	Matrix(Matrix* matrix);

	~Matrix();

	int getColumnsCount();

	int getStringsCount();

	int getElement(int i, int j);

	void setElement(int i, int j, int value);

	bool isEmpty();

	void printMatrix();

	int** getRawMatrix();

	int** copyRawMatrix();

private:

	bool checkRange(int i, int j);
};

