#include "stdafx.h"

CMatrixMutator::CMatrixMutator() : MatrixMutator()
{}


CMatrixMutator::~CMatrixMutator()
{}

void CMatrixMutator::executeAndProcedure(Matrix* matrix, int andValue)
{
	int stringsCount = matrix->getStringsCount();
	int columnsCount = matrix->getColumnsCount();
	for (int i = 0; i < stringsCount; i++)
		for (int j = 0; j < columnsCount; j++)
		{
			matrix->setElement(i, j, matrix->getElement(i, j) & andValue);
		}
}
