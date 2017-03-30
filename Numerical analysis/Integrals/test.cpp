#define _USE_MATH_DEFINES
#include "Integral.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

func_t source_func = [](double x) {return (exp(x) * x); };
func_t test_func = [](double x) {return  (exp(x) * (x - 1)); };

const double a = -1.0;
const double b = 10.0;
const double true_answer = test_func(b) - test_func(a);
const double M = fabs(exp(b) * (b + 2));
const double eps = 1e-5;
const double h = sqrt((12 * eps) / ((b - a) * M));

/*
	True answer of integration from -1 to 10 range is 198.239
*/

void print_head_ftable()
{
	printf("Function: e^x * x from %+3.2f to %+3.2f, with eps = %1.5e:\n", a, b, eps);
	printf("Trapezium rule:\n");
	printf("+=============+================+==================+=================+\n");
	printf("|     eps     |        h       |     Integral     |      Error      |\n");
	printf("+=============+================+==================+=================+\n");
};

void print_head_stable()
{
	printf("\n\nRefined calculation:\n");
	printf("+=================+================+=================+\n");
	printf("|       eps       |       h        |      Error      |\n");
	printf("+=================+================+=================+\n");
};

void print_line_ftask(double eps, double h, double true_answer, double error)
{
	printf("| %11.1e | %3.8e |  %10.8e  | %10.9e |\n", eps, h, true_answer, error);
	printf("+=============+================+==================+=================+\n");
};

void print_line_stask(double eps, double h, double error)
{
	printf("| %10.9e | %3.8e | %10.9e |\n", eps, h, error);
	printf("+=================+================+=================+\n");
};

void integral_test()
{
	print_head_ftable();
	double result = integral(source_func, a, b, h);
	print_line_ftask(eps, h, true_answer, fabs(result - true_answer));
};

void refined_calc_test()
{
	double real_error = fabs(integral(source_func, a, b, h) - true_answer);

	double h_refined = (b - a) * sqrt(real_error);
	double result = integral(source_func, a, b, h_refined);
	h_refined /= 2.0;
	double refined_calc = integral(source_func, a, b, h);

	print_head_stable();

	while ((fabs(refined_calc - result)) >= real_error * 3.0)
	{
		result = refined_calc;
		h_refined /= 2.0;
		refined_calc = integral(source_func, a, b, h_refined);
	}
	print_line_stask(real_error, h_refined, fabs(refined_calc - true_answer));

	printf("abs(I2 - I1) = %10.9e\n\n", fabs(refined_calc - result));
};

void make_tests()
{
	integral_test();
	refined_calc_test();
	system("pause");
};

int main()
{
	make_tests();
	return 0;
};