#pragma once

#include "stdafx.h"

class CMatrixMutator : public MatrixMutator
{
public:

	CMatrixMutator();

	~CMatrixMutator();

	void executeAndProcedure(Matrix* matrix, int begin, int end, int step);
};

