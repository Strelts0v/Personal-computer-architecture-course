#include "stdafx.h"

MatrixFactory::MatrixFactory()
{}


MatrixFactory::~MatrixFactory()
{}

Matrix* MatrixFactory::getMatrix(int stringsCount, int columnsCount, int startOfInterval, int endOfInterval)
{
	Matrix* matrix = new Matrix(stringsCount, columnsCount);
	if (matrix->isEmpty())
	{
		return NULL;
	}
	if (startOfInterval < 0 || endOfInterval > RAND_MAX) 
	{
		printf("Invalid interval for values of matrix! Returning matrix elements has 0 values...\n");
		fillZeroValues(matrix);
	}
	else {
		fillRandomized(matrix, startOfInterval, endOfInterval);
	}
	return matrix;
}

void MatrixFactory::fillRandomized(Matrix* matrix, int begin, int end)
{
	srand(time(NULL));
	int stringsCount = matrix->getStringsCount();
	int columnsCount = matrix->getColumnsCount();
	for(int i = 0; i < stringsCount; i++)
		for (int j = 0; j < columnsCount; j++)
		{
			matrix->setElement(i, j, rand() % (end - begin + 1) + begin);
		}
}

void MatrixFactory::fillZeroValues(Matrix* matrix)
{
	int stringsCount = matrix->getStringsCount();
	int columnsCount = matrix->getColumnsCount();
	for (int i = 0; i < stringsCount; i++)
		for (int j = 0; j < columnsCount; j++)
		{
			matrix->setElement(i, j, 0);
		}
}