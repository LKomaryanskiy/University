#include "equation.h"
#include <stdio.h>

const double a = 0.0;
const double b = 1.5;
const double eps_beg = 1e-2;
const double eps_step = 1e-3;
const double eps_limit = 1e-15;


func_t func = [](double x)->double {return (x*x*x - x + cos(x + M_PI / 4.0) - 1); };
func_t func_deriv = [](double x)->double {return (3 * x * x - 1 - sin(x + M_PI / 4.0)); };

void print_result_head()
{
	printf("+==============+=====+==================+=================+\n");
	printf("|      eps     |  n  |     Accuracy     |      Value      |\n");
	printf("+==============+=====+==================+=================+\n");
};

void print_result(double eps, SolveInfo sf)
{
	printf("| %4e | %3d |  %1.12f  | %+1.12f |\n", eps, sf.steps, sf.accuracy, sf.value);
	printf("+==============+=====+==================+=================+\n");
};

void print_speed_result_head()
{
	printf("+==============+===========+=============+\n");
	printf("|     eps      |  n(iter)  |  n(bisect)  |\n");
	printf("+==============+===========+=============+\n");
};

void print_speed_result(double eps, SolveInfo iter_info, SolveInfo bisection_info)
{
	printf("| %4e | %9d | %11d |\n", eps, iter_info.steps, bisection_info.steps);
	printf("+==============+===========+=============+\n");
};

void bisection_test()
{
	double curr_eps = eps_beg;
	printf("Bisection on [%+f, %+f] range:\n", a, b);
	print_result_head();
	while (curr_eps >= eps_limit)
	{
		print_result(curr_eps, bisection(curr_eps, a, b, func));
		curr_eps *= eps_step;
	}
	printf("\n");
};

void iteration_test()
{
	double curr_eps = eps_beg;
	printf("Iteration on [%+f, %+f] range:\n", a, b);
	print_result_head();
	while (curr_eps >= eps_limit)
	{
		print_result(curr_eps, iteration(curr_eps, a, b, func, func_deriv));
		curr_eps *= eps_step;
	}
	printf("\nSpeed tests:\n");
};

void speed_test()
{
	double curr_eps = eps_beg;
	print_speed_result_head();
	while (curr_eps >= eps_limit)
	{
		print_speed_result(curr_eps, iteration(curr_eps, a, b, func, func_deriv), bisection(curr_eps, a, b, func));
		curr_eps *= eps_step;
	}
};

void make_test()
{
	bisection_test();
	iteration_test();
	speed_test();
	system("pause");
};

int main()
{
	make_test();
	return 0;
};