#include "stdafx.h"

MmxMatrixMutator::MmxMatrixMutator() : MatrixMutator()
{}


MmxMatrixMutator::~MmxMatrixMutator()
{}

void MmxMatrixMutator::executeAndProcedure(Matrix* matrix, int begin, int end, int step)
{
	int** originalMatrix = matrix->getRawMatrix();
	const int stringsCount = MATRIX_DIMENSION;
	const int columnsCount = MATRIX_DIMENSION;
	const int halfOfColumnsCount = columnsCount / 2;
	int rawMatrix[columnsCount][stringsCount];
	for (int i = 0; i < stringsCount; i++)
		for (int j = 0; j < columnsCount; j++)
		{
			rawMatrix[i][j] = originalMatrix[i][j];
		}
	int andValues[2];
	clock_t time = clock();
	for (begin; begin <= end; begin += step)
	{
		_asm {
			mov edi, begin
			mov andValues[0], edi
			mov andValues[4], edi
			movq MM0, stringsCount			
			pmullw MM0, columnsCount
			movd ecx, MM0					// number of elements in array
			xor esi, esi					// current index
			movq MM1, andValues[0]			// value for "AND" operation
		BEGIN :
			movq MM2, rawMatrix[esi * 4]
			pand MM2, MM1
			movq rawMatrix[esi * 4], MM2
			inc esi
			inc esi
			sub ecx, 1
			loop BEGIN
			emms
		}
	}
	printf("\nCalculating time using MMX technology: %d\n", clock() - time);
	// saving changes to original matrix:
	for (int i = 0; i < stringsCount; i++)
		for (int j = 0; j < columnsCount; j++)
		{
			originalMatrix[i][j] = rawMatrix[i][j];
		}
}
