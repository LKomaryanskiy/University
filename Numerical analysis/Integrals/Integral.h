#pragma once
#include <stdio.h>
#include <math.h>

typedef double(*func_t)(double x);

//Trapezium rule
double integral(func_t func, double a, double b, double h);