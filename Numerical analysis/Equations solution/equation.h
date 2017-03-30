#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

typedef double(*func_t)(double x);

struct SolveInfo
{
	double	value;
	int		steps;
	double	accuracy;
};

SolveInfo iteration(double eps, double a, double b, func_t func, func_t deriv_func);

SolveInfo bisection(double eps, double a, double b, func_t func);