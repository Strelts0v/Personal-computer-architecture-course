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
	int rawMatrix[columnsCount][stringsCount];
	for (int i = 0; i < stringsCount; i++)
		for (int j = 0; j < columnsCount; j++)
		{
			rawMatrix[i][j] = originalMatrix[i][j];
		}
	_asm finit
	_asm {
		movq MM0, stringsCount
		pmullw MM0, columnsCount
		movd ecx, MM0					// number of elements in array
		xor esi, esi					// current index
		movq MM1, andValue				// value for "AND" operation
	BEGIN:
		movq MM2, rawMatrix[esi * 4]
		PAND MM2, MM1
		movd rawMatrix[esi * 4], MM2
		inc esi
		loop BEGIN
		emms
	}
	// saving changes to original matrix:
	for (int i = 0; i < stringsCount; i++)
		for (int j = 0; j < columnsCount; j++)
		{
			originalMatrix[i][j] = rawMatrix[i][j];
		}
}
