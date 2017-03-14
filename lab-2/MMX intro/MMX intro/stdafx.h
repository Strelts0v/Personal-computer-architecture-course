// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>
#include <ctime>

// addtional custom headers
#include "Matrix.h"
#include "MatrixMutator.h"
#include "MatrixFactory.h"
#include "AsmMatrixMutator.h"
#include "CMatrixMutator.h"
#include "MmxMatrixMutator.h"

#define _CRT_SECURE_NO_WARNINGS
#define MATRIX_DIMENSION 16

double inputNumber();
