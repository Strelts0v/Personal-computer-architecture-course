#include "stdafx.h"

MmxMatrixMutator::MmxMatrixMutator() : MatrixMutator()
{}


MmxMatrixMutator::~MmxMatrixMutator()
{}

void MmxMatrixMutator::executeAndProcedure(Matrix* matrix, int andValue)
{
	int** originalMatrix = matrix->getRawMatrix();
	const int stringsCount = MATRIX_DIMENSION;
	const int columnsCount = MATRIX_DIMENSION;
	//int sizeOfElement = sizeof(int);
	int rawMatrix[columnsCount][stringsCount];
	for (int i = 0; i < stringsCount; i++)
	{
		for (int j = 0; j < columnsCount; j++)
		{
			rawMatrix[i][j] = originalMatrix[i][j];
		}
	}
	printf("\n\nbefore:\n");
	for (int i = 0; i < stringsCount; i++)
	{
		printf("|");
		for (int j = 0; j < columnsCount; j++)
		{
			printf("%6d", rawMatrix[i][j]);
		}
		printf(" |\n");
	}
	_asm finit
	_asm {
		movq MM0, stringsCount
		pmullw MM0, columnsCount
		movd ecx, MM0					// number of elements in array
		xor esi, esi					// current index
		movq MM1, andValue				// value for "AND" operation
	BEGIN:
		//PAND rawMatrix[esi * 4], andValue
		movq MM2, rawMatrix[esi * 4]
		PAND MM2, MM1
		movd rawMatrix[esi * 4], MM2
		inc esi
		loop BEGIN
	}
	// reading:
	printf("\n\nResult matrix:\n");
	for (int i = 0; i < stringsCount; i++)
	{
		printf("|");
		for (int j = 0; j < columnsCount; j++)
		{
			printf("%3d", rawMatrix[i][j]);
		}
		printf(" |\n");
	}
}
