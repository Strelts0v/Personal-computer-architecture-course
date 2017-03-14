#pragma once

#include "stdafx.h"

class AsmMatrixMutator : public MatrixMutator
{
public:

	AsmMatrixMutator();

	~AsmMatrixMutator();

	void executeAndProcedure(Matrix* matrix, int begin, int end, int step);
};
