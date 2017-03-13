// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	Matrix* matrix1 = MatrixFactory::getMatrix(MATRIX_DIMENSION, MATRIX_DIMENSION, 4, 4477);
	Matrix* matrix2 = new Matrix(matrix1);
	Matrix* matrix3 = new Matrix(matrix1);

	printf("Matrix initialization:\n");
	matrix1->printMatrix();

	printf("\n\nMatrix after AND operation (C):\n");
	MatrixMutator* cMatrixMutator = new CMatrixMutator();
	cMatrixMutator->executeAndProcedure(matrix1, 4);
	matrix1->printMatrix();

	printf("\n\nMatrix after AND operation (ASM):\n");
	MatrixMutator* asmMatrixMutator = new AsmMatrixMutator();
	asmMatrixMutator->executeAndProcedure(matrix2, 4);
	matrix2->printMatrix();

	printf("\n\nMatrix after AND operation (MMX):\n");
	MatrixMutator* mmxMatrixMutator = new MmxMatrixMutator();
	mmxMatrixMutator->executeAndProcedure(matrix3, 4);
	matrix3->printMatrix();
	
	_getch();
	return 0;
}

