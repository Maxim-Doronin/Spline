#pragma once

#include <math.h>
#include <limits>
#include "string.h"
#include "iostream"
#include <stdio.h>
#include <tchar.h>

class TSpline
{
private:
	struct splineVariables
	{
		double A, B, C, D, x;
	};

	splineVariables *splines;
	int pointsCount;
	void freeMemory();

public:
	TSpline();
	~TSpline();
	void buildSplines(const double *x, const double *y, const int& n);
	double getInterpolatedFunctionValue(const double& arg);
};

double calculateFunction(double x);