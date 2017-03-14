#include "stdafx.h"

AsmMatrixMutator::AsmMatrixMutator() : MatrixMutator()
{}


AsmMatrixMutator::~AsmMatrixMutator()
{}

void AsmMatrixMutator::executeAndProcedure(Matrix* matrix, int begin, int end, int step)
{
	int** originalMatrix = matrix->getRawMatrix();
	const int stringsCount = MATRIX_DIMENSION;
	const int columnsCount = MATRIX_DIMENSION;
	//int sizeOfElement = sizeof(int);
	int rawMatrix[columnsCount][stringsCount];
	for (int i = 0; i < stringsCount; i++)
		for (int j = 0; j < columnsCount; j++)
		{
			rawMatrix[i][j] = originalMatrix[i][j];
		}
	clock_t time = clock();
	for (begin; begin <= end; begin += step)
	{
		_asm {
			mov eax, stringsCount
			mul columnsCount
			mov ecx, eax				// number of elements in array
			xor esi, esi                // current index
		BEGIN :
			mov edi, rawMatrix[esi * 4]
			and edi, begin
			mov rawMatrix[esi * 4], edi
			inc esi
			loop BEGIN
		}
	}
	printf("\nCalculating time in Assembler language: %d\n", clock() - time);
	// saving changes to original matrix:
	for(int i = 0; i < stringsCount; i++)
		for (int j = 0; j < columnsCount; j++)
		{
			originalMatrix[i][j] = rawMatrix[i][j];
		}
}
