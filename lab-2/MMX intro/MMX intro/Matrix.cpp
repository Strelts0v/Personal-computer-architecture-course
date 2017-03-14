#include "stdafx.h"
#include "Matrix.h"

Matrix::Matrix(int stringsCount, int columnsCount)
{
	this->columnsCount = columnsCount;
	this->stringsCount = stringsCount;
	this->matrix = new int*[stringsCount];
	if (this->matrix == NULL)
	{
		printf("Error! Not enough memory for matrix...\n");
		this->matrix = NULL;
		this->columnsCount = 0;
		this->stringsCount = 0;
	}
	else {
		for (int i = 0; i < stringsCount; i++)
		{
			this->matrix[i] = new int[columnsCount];
			if (this->matrix[i] == NULL)
			{
				printf("Error! Not enough memory for matrix...\n");
				for (i; i >= 0; i--)
				{
					delete this->matrix[i];
				}
				delete matrix;
				this->matrix = NULL;
				this->columnsCount = 0;
				this->stringsCount = 0;
			}
		}
	}
}

Matrix::Matrix(Matrix* matrix)
{
	this->columnsCount = matrix->columnsCount;
	this->stringsCount = matrix->stringsCount;
	this->matrix = new int*[stringsCount];
	if (this->matrix == NULL)
	{
		printf("Error! Not enough memory for matrix...\n");
		this->matrix = NULL;
		this->columnsCount = 0;
		this->stringsCount = 0;
	}
	else {
		for (int i = 0; i < stringsCount; i++)
		{
			this->matrix[i] = new int[columnsCount];
			if (this->matrix[i] == NULL)
			{
				printf("Error! Not enough memory for matrix...\n");
				for (i; i >= 0; i--)
				{
					delete this->matrix[i];
				}
				delete matrix;
				this->matrix = NULL;
				this->columnsCount = 0;
				this->stringsCount = 0;
			}
			else {
				for (int j = 0; j < columnsCount; j++)
				{
					this->matrix[i][j] = matrix->getElement(i, j);
				}
			}
		}
	}
}

Matrix::~Matrix()
{
	for (int i = stringsCount - 1; i >= 0; i--)
	{
		delete this->matrix[i];
	}
	delete matrix;
}

int Matrix::getColumnsCount()
{
	return this->columnsCount;
}

int Matrix::getStringsCount()
{
	return this->stringsCount;
}

int Matrix::getElement(int i, int j)
{
	if (checkRange(i, j))
	{
		return matrix[i][j];
	}
	else {
		printf("Error! Illegal matrix indexes for getting element...\n");
		return -1;
	}
}

void Matrix::setElement(int i, int j, int value)
{
	if (checkRange(i, j))
	{
		matrix[i][j] = value;
	}
	else {
		printf("Error! Illegal matrix indexes for setting element...\n");
	}
}

bool Matrix::isEmpty()
{
	return (this->matrix == NULL) ? true : false;
}

void Matrix::printMatrix()
{
	for (int i = 0; i < this->stringsCount; i++)
	{
		printf("|");
		for (int j = 0; j < this->columnsCount; j++)
		{
			printf("%6d", this->matrix[i][j]);
		}
		printf(" |\n");
	}
}

int** Matrix::getRawMatrix()
{
	return this->matrix;
}

int** Matrix::copyRawMatrix()
{
	int columnsCount = this->columnsCount;
	int stringsCount = this->stringsCount;
	int** matrix = new int*[stringsCount];
	if (matrix == NULL)
	{
		printf("Error! Not enough memory for matrix...\n");
		matrix = NULL;
	}
	else {
		for (int i = 0; i < stringsCount; i++)
		{
			matrix[i] = new int[columnsCount];
			if (matrix[i] == NULL)
			{
				printf("Error! Not enough memory for matrix...\n");
				for (i; i >= 0; i--)
				{
					delete matrix[i];
				}
				delete matrix;
				matrix = NULL;
			}
		}
	}
	for(int i = 0; i < stringsCount; i++)
		for (int j = 0; j < columnsCount; j++)
		{
			matrix[i][j] = this->matrix[i][j];
		}
	return matrix;
}

bool Matrix::checkRange(int i, int j)
{
	if (i < 0 || i > this->stringsCount - 1 || j < 0 || j > this->columnsCount - 1) {
		return false;
	}
	return true;
}