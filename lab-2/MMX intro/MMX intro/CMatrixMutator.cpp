#include "stdafx.h"

CMatrixMutator::CMatrixMutator() : MatrixMutator()
{}


CMatrixMutator::~CMatrixMutator()
{}

void CMatrixMutator::executeAndProcedure(Matrix* matrix, int begin, int end, int step)
{
	clock_t time = clock();
	for (begin; begin <= end; begin += step) 
	{
		int stringsCount = matrix->getStringsCount();
		int columnsCount = matrix->getColumnsCount();
		int andValue = begin;
		for (int i = 0; i < stringsCount; i++)
			for (int j = 0; j < columnsCount; j++)
			{
				matrix->setElement(i, j, matrix->getElement(i, j) & andValue);
			}
	}
	printf("\nCalculating time in C language: %d\n", clock() - time);
}
