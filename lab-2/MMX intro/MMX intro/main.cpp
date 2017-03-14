// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	int flag = 1;
	do {
		printf("Matrix initialization:\n");
		Matrix* matrix1 = MatrixFactory::getMatrix(MATRIX_DIMENSION, MATRIX_DIMENSION, 4, 4477);
		Matrix* matrix2 = new Matrix(matrix1);
		Matrix* matrix3 = new Matrix(matrix1);
		matrix1->printMatrix();

		int a = 0, b = 0, step;
		printf("\nInput values for calculating interval:\n");
		printf("Input begin of interval: ");
		do {
			a = (int)inputNumber();
		} while (a < 0);
		printf("\nInput end of interval: ");
		do {
			b = (int)inputNumber();
		} while (b < 0 || b < a);
		printf("\nInput step for interval: ");
		do {
			step = (int)inputNumber();
		} while (step <= 0);

		printf("\nCase with 'AND' operation in C language");
		MatrixMutator* cMatrixMutator = new CMatrixMutator();
		cMatrixMutator->executeAndProcedure(matrix1, a, b, step);
		matrix1->printMatrix();

		printf("\nCase with 'AND' operation in Assembler language");
		MatrixMutator* asmMatrixMutator = new AsmMatrixMutator();
		asmMatrixMutator->executeAndProcedure(matrix2, a, b, step);
		matrix2->printMatrix();

		printf("\nCase with 'AND' operation using MMX technology");
		MatrixMutator* mmxMatrixMutator = new MmxMatrixMutator();
		mmxMatrixMutator->executeAndProcedure(matrix3, a, b, step);
		matrix3->printMatrix();

		printf("\nEnter 0 to exit or something else to continue: ");
		flag = inputNumber();
		system("cls");
	} while (flag != 0);
	return 0;
}

