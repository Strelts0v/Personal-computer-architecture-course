#pragma once

#include "stdafx.h"

class MatrixMutator
{
public:

	MatrixMutator();

	~MatrixMutator();

	virtual void executeAndProcedure(Matrix* matrix, int andValue) = 0;
};

