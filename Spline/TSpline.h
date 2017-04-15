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
		double a, b, c, d, x;
	};

	splineVariables *splines;
	int pointsCount;
	void freeMemory();

public:
	TSpline();
	~TSpline();
	void buildSplines(const double *x, const double *y, int n);
	double getInterpolatedFunctionValue(double arg);
};

double calculateFunction(double x);