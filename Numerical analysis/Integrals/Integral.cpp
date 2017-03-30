#include "Integral.h"

double integral(func_t func, double a, double b, double h)
{
	//Recalculate step
	unsigned long int n = (b - a) / h;
	h = (b - a) / double(n);

	double ret_value = (func(a) + func(b)) / 2.0;
	for (unsigned long int i = 1; i < n; ++i)
	{
		ret_value += func(a + i * h);
	}
	ret_value *= h;

	return ret_value;
};
