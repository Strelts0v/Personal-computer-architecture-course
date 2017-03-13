#pragma once

#include "stdafx.h"

using namespace std;

class MatrixFactory
{
private:

	MatrixFactory();

	~MatrixFactory();

public:

	static Matrix* getMatrix(int stringsNumber, int columnsNumber, int startOfInterval, int endOfInterval);

private:

	static void fillRandomized(Matrix* matrix, int begin, int end);

	static void fillZeroValues(Matrix* matrix);

};

