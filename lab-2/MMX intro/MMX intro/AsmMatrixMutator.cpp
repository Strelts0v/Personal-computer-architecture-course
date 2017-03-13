#include "stdafx.h"

AsmMatrixMutator::AsmMatrixMutator() : MatrixMutator()
{}


AsmMatrixMutator::~AsmMatrixMutator()
{}

void AsmMatrixMutator::executeAndProcedure(Matrix* matrix, int andValue)
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
		mov eax, stringsCount
		mul columnsCount
		mov ecx, eax				// number of elements in array
		xor esi, esi                // current index
		BEGIN:
		mov edi, rawMatrix[esi * 4]
		and edi, andValue
		mov rawMatrix[esi * 4], edi
		inc esi
		loop BEGIN
	}
	_asm fwait
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
