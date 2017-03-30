#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

struct CosInfo{
	double	eps;
	int		n;
	double	absError;
	double	remTerm;
	double	value;
};

class MyCos{
public:
	MyCos(double firstEps = 0.01, double epsMultiplier = 0.001, double epsLimit = 0.00000000000001 /*10^(-14)*/) :
		cFirstEps(firstEps), cEpsMultipier(epsMultiplier), cEpsLimit(epsLimit) {};
	void CalculateExpressions(double x);
	//Return value, that has less eps or most accurate
	//If  doesn't get parameter return most accurate value
	double GetExpression(double eps = 0.00000000000001);
	double GetAbsError(double eps = 0.00000000000001);
	double GetRemainderTerm(double eps = 0.00000000000001);
	void PrintTable();
protected:
	std::vector<CosInfo>	mCosInfo;
	const double			cFirstEps;
	const double			cEpsMultipier;
	const double			cEpsLimit;
};