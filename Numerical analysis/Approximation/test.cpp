#include "Approximation.h"
#include <stdio.h>
#include <iostream>

//f = (x^2 - sin(x)) * cos(2.5 * x)) Range: [0.0, 7.0]. precition = 0.01
func_t source_func = [](double x) {return ((x * x - sin(x)) * cos(2.5 * x)); };

const double a = 0.0;
const double b = 7.0;
const double eps = 1e-2;
const unsigned int start_n = 5;


int main()
{
	Approximation approximation(source_func, a, b, eps, start_n, true);
	std::vector<double> pol =  approximation.Calculate();
	try
	{
		approximation.SaveToFile();
	}
	catch (std::exception& ex)
	{
		printf(ex.what());
	}
	system("pause");
	return 0;
};