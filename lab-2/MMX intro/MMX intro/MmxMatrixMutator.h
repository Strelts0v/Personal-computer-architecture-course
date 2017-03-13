#pragma once

#include "stdafx.h"

class MmxMatrixMutator : public MatrixMutator
{
public:

	MmxMatrixMutator();

	~MmxMatrixMutator();

	void executeAndProcedure(Matrix* matrix, int andValue);
};

