#include "equation.h"


SolveInfo iteration(double eps, double a, double b, func_t func, func_t deriv_func)
{
	SolveInfo ret_value{ 0.0, 0, 0.0 };
	double deriv_value_a = std::fabs(deriv_func(a));
	double deriv_value_b = std::fabs(deriv_func(b));

	double lambda = 1 / std::max(deriv_value_a, deriv_value_b);
	
	double q = 1 - std::min(deriv_value_a, deriv_value_b) / std::max(deriv_value_a, deriv_value_b);
	double xk, x0 = (b + a) / 2.0;
	const double sign = deriv_func(x0) ? 1.0 : -1.0;
	xk = x0 - lambda * sign * (func(x0));
	double precision = abs(((1 - q) / q ) * eps);
	

	while (abs(xk - x0) > precision)
	{
		x0 = xk;
		xk = xk - lambda * sign * (func(xk));
		++ret_value.steps;
	}

	ret_value.value = xk;
	ret_value.accuracy = std::abs(q * abs(xk - x0) / (1 - q));

	return ret_value;
};

SolveInfo bisection(double eps, double a, double b, func_t func)
{
	SolveInfo ret_value{ 0.0, 0, 0.0 };
	double c;

	while ((b - a) > eps * 2.0)
	{
		c = (b + a) / 2.0;
		if (func(c) * func(a) < 0)
			b = c;
		else
			a = c;
		++ret_value.steps;
	}

	ret_value.value = (a + b) / 2.0;
	ret_value.accuracy = abs((b - a) / 2.0);

	return ret_value;
};
