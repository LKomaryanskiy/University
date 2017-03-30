#include "SplineInterpolation.h"
#include <stdlib.h>

const double a = 0.0;
const double b = 7.0;
//f = (x^2 - sin(x)) * cos(2.5 * x)) Range: [0.0, 7.0]. precition = 0.01
func_t source_func = [](double x) {return ((x * x - sin(x)) * cos(2.5 * x)); };
//Amount of section
const unsigned int n = 40;
//Amount of interpolation points
const unsigned int interpolation_points = 100;
const std::string file_path = "plots.csv";

void make_test()
{
	printf("Spline interpolation starts!\n");
	SplineInterpolation inter(source_func, a, b, n);
	std::vector<vector2d> result = inter.Calculate(interpolation_points);
	inter.SaveToFile(file_path);
	printf("Done!\n");
	printf("Calculated %d plots using %d points by function in range[%2.3f, %2.3f]\n", interpolation_points, n, a, b);
	printf("Results printed in %s\n", file_path.c_str());
	system("pause");
};

int main()
{
	make_test();
	return 0;
}