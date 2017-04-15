#include "TSpline.h"

double calculateFunction(double x)
{
	double result = pow(x, 5) - 3 * pow(x, 4) - 10 * pow(x, 3) + 50 * x*x + 100 * x;
	result /= (x*x + 2 * x + 2);
	return result;
}

TSpline::TSpline()
{
	splines = NULL;
}

TSpline::~TSpline()
{
	freeMemory();
}

void TSpline::buildSplines(const double *x, const double *y, int n)
{
	freeMemory();
	pointsCount = n;
	splines = new splineVariables[pointsCount];
	for (int i = 0; i < pointsCount; i++)
	{
		splines[i].x = x[i];
		splines[i].a = y[i];
	}
	splines[0].c = splines[pointsCount - 1].c = 0.0;

	double *alpha = new double[n - 1];
	double *beta = new double[n - 1];
	alpha[0] = beta[0] = 0.0;

	for (int i = 1; i < pointsCount - 1; i++)
	{
		double h_i = x[i] - x[i - 1];
		double h_i1 = x[i + 1] - x[i];
		double A = h_i;
		double C = 2. * (h_i + h_i1);
		double B = h_i1;
		double F = 6.0 * ((y[i + 1] - y[i]) / h_i1 - (y[i] - y[i - 1]) / h_i);
		double z = (A * alpha[i - 1] + C);
		alpha[i] = -B / z;
		beta[i] = (F - A * beta[i - 1]) / z;
	}

	for (int i = pointsCount - 2; i > 0; --i)
	{
		splines[i].c = alpha[i] * splines[i + 1].c + beta[i];
	}

	for (int i = pointsCount - 1; i > 0; --i)
	{
		double h_i = x[i] - x[i - 1];
		splines[i].d = (splines[i].c - splines[i - 1].c) / h_i;
		splines[i].b = h_i * (2.0 * splines[i].c + splines[i - 1].c) / 6.0 + (y[i] - y[i - 1]) / h_i;
	}

	delete[] beta;
	delete[] alpha;
}

double TSpline::getInterpolatedFunctionValue(double arg)
{
	if (!splines)
	{
		return std::numeric_limits<double>::quiet_NaN();
	}

	splineVariables* s;
	if (arg <= splines[0].x)
	{
		s = splines + 1;
	}
	else
	{
		if (arg >= splines[pointsCount - 1].x)
		{
			s = splines + pointsCount - 1;
		}
		else
		{
			int i = 0, j = pointsCount - 1;
			while (i + 1 < j)
			{
				int k = i + (j - i) / 2;
				if (arg <= splines[k].x)
					j = k;
				else
					i = k;
			}
			s = splines + j;
		}
	}
	double dx = (arg - s->x);
	return s->a + (s->b + (s->c / 2.0 + s->d * dx / 6.0) * dx) * dx;
}

void TSpline::freeMemory()
{
	if (splines)
	{
		delete[] splines;
		splines = NULL;
	}
}