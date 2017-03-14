#pragma once

#include "stdafx.h"

class MatrixMutator
{
public:

	MatrixMutator();

	~MatrixMutator();

	virtual void executeAndProcedure(Matrix* matrix, int begin, int end, int step) = 0;
};

