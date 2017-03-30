#include "MatrixSolver.h"
#include <stdio.h>
#include <math.h>

/*
	
	Source matrix:
	12	6	2	16	|148
	18	0	34	15	|230
	20	56	18	17	|218
	2	5	17	17	|144

	Exact solution
	x1 = 4
	x2 = 0
	x3 = 2
	x4 = 6

	Transformed matrix for iteration method:
	x1 = 90/26  +	0*x1     +	4/26*x2  -	2/26*x3  +	3/26*x4
	x2 = 218/56 -	20/56*x1 +	0*x2     -	18/56*x3 -	17/56*x4
	x3 = 230/34 -	18/34*x1 +	0*x2     +	0*x3     -	15/34*x4
	x4 = 650/83 -	34/83*x1 -	34/83*x2 -	8/83*x3  +	0*x4

*/

const int amount_of_roots = 4;

const std::vector<std::vector<double>> source_matrix =
{
	{ 12.0, 6.0, 2.0, 16.0, 148.0 },
	{ 18.0, 0.0, 34.0, 15.0, 230.0 },
	{ 20.0, 56.0, 18.0, 17.0, 218.0 },
	{ 2.0, 5.0, 17.0, 17.0, 144.0 }
};

//Parameters for iteration method
const double eps = 1e-6;	
const std::vector<std::vector<double>> iteration_matrix = 
{
	{90/26.0, 0.0, 4/26.0, -2/26.0, 3/26.0},
	{218/56.0, -20/56.0, 0.0, -18/56.0, -17/56.0},
	{230/34.0, -18/34.0, 0.0, 0.0, -15/34.0},
	{650/83.0, -34/83.0, -34/83.0, -8/83.0, 0.0}
};

void print_answer(std::vector<double> result)
{
	printf("Error in first equation = %f3 \n", abs(148.0 - (12 * result[0] + 6 * result[1] + 2 * result[2] + 16 * result[3])));
	printf("Error in second equation = %f3 \n", abs(230.0 - (18 * result[0] + 34 * result[2] + 15 * result[3])));
	printf("Error in third equation = %f3 \n", abs(218.0 - (20 * result[0] + 56 * result[1] + 18 * result[2] + 17 * result[3])));
	printf("Error in fourth equation = %f3 \n", abs(144.0 - (2 * result[0] + 5 * result[1] + 17 * result[2] + 17 * result[3])));
};

void test_iteration()
{
	std::vector<double> result = direct_iteration(iteration_matrix, eps);
	printf("Iteration method, roots (eps = %1.3e):\n", eps);
	for (int i = 0; i < amount_of_roots; ++i)
	{
		printf("x%d = %f3\n", i, result[i]);
	}
	print_answer(result);
};

void test_gaussian()
{
	std::vector<double> result = gaussian_elimination(source_matrix);
	printf("Gaussian method, roots:\n");
	for (int i = 0; i < amount_of_roots; ++i)
	{
		printf("x%d = %f3\n", i, result[i]);
	}
	print_answer(result);
};

void test_complete_pivoting()
{
	std::vector<double> result = complete_pivoting(source_matrix);
	printf("Complete pivoting method, roots:\n");
	for (int i = 0; i < amount_of_roots; ++i)
	{
		printf("x%d = %f3\n", i, result[i]);
	}
	print_answer(result);
};

void make_test()
{
	test_iteration();
	printf("\n");
	test_gaussian();
	printf("\n");
	test_complete_pivoting();

	system("pause");
};

int main()
{
	make_test();
	return 0;
};