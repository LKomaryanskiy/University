#include "MyCos.h"


//Constants for my variant
const double eps = 0.00000001; // 10^(-8)
const double a = -3.3;
const double b = 24.9;
const int n = 10;

//Second task
void test_in_interval(){
	MyCos myCos(eps, 0.1, eps);
	double h = (b - a) / (double)n;
	printf("+==================+=================+=================+\n");
	printf("|       x(i)       | Absolute error  |  Remainder term |\n");
	printf("+==================+=================+=================+\n");
	for (int i = 0; i <= n; i++){
		//x(i)
		double x = a + h * i;
		myCos.CalculateExpressions(x);
		printf("| %-+2.12f | %+1.12f | %+1.12f |\n", x, myCos.GetAbsError(), myCos.GetRemainderTerm());
		printf("+==================+=================+=================+\n");
	}
};

int main(){
	MyCos myCos;
	double x = (b - a) / 2;
	myCos.CalculateExpressions(x);
	myCos.PrintTable();
	system("pause");
	system("cls");
	test_in_interval();
	system("pause");
	return 0;
};