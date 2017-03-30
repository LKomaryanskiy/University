#include "MyCos.h"

void MyCos::CalculateExpressions(double x){
	//Limit x between 0 and Pi
	//Since cos is even function, we can take absolute x value
	//This guarantees less iterations
	double limitedX = [x]() -> double{	double tmp = (fabs(x) - 2 * M_PI * floor(fabs(x) / (M_PI * 2))); 
										return (tmp >= M_PI) ? (2 * M_PI - tmp) : tmp; } ();
	//Limit x between 0 and Pi/2
	int startCoef = [&limitedX]() -> int {	if (limitedX >= M_PI / 2){
												limitedX = M_PI - limitedX;
												return - 1;
											}; 
											return 1; }();
	double currentEps = cFirstEps;
	double cosValue = 0;
	double currTerm = startCoef;
	double remTerm = (limitedX * limitedX) / (12.0);
	int n = 1;
	
	while (currentEps >= cEpsLimit){
		remTerm = (-1 * (limitedX * limitedX) * currTerm) / (2.0 * n * (2.0 * n - 1.0));
		cosValue += currTerm;

		if (currentEps >= fabs(remTerm)){
			CosInfo tmpCosInfo;
			tmpCosInfo.eps = currentEps;
			tmpCosInfo.n = n;
			tmpCosInfo.absError = fabs(cos(x) - cosValue);
			tmpCosInfo.remTerm = remTerm;
			tmpCosInfo.value = cosValue;
			mCosInfo.push_back(tmpCosInfo);

			currentEps *= cEpsMultipier;
		}
		n++;
		currTerm = remTerm;
	};
};

double MyCos::GetExpression(double eps){
	auto it = std::find_if(mCosInfo.begin(), mCosInfo.end(), [eps](const CosInfo& elem)->bool{
		return (eps >= elem.eps);
	});
	if (it != mCosInfo.end()){
		return it->value;
	}
	return mCosInfo[mCosInfo.size() - 1].value;
};

double MyCos::GetAbsError(double eps){
	auto it = std::find_if(mCosInfo.begin(), mCosInfo.end(), [eps](const CosInfo& elem)->bool{
		return (eps >= elem.eps);
	});
	if (it != mCosInfo.end()){
		return it->absError;
	}
	return mCosInfo[mCosInfo.size() - 1].absError;
};

double MyCos::GetRemainderTerm(double eps){
	auto it = std::find_if(mCosInfo.begin(), mCosInfo.end(), [eps](const CosInfo& elem)->bool{
		return (eps >= elem.eps);
	});
	if (it != mCosInfo.end()){
		return it->remTerm;
	}
	return mCosInfo[mCosInfo.size() - 1].remTerm;
};

void MyCos::PrintTable(){
	printf("+=================+=====+=================+=================+=================+\n");
	printf("|       eps       |  n  | Absolute error  | Remainder term  |      Value      |\n");
	printf("+=================+=====+=================+=================+=================+\n");
	for (const CosInfo& i : mCosInfo){
		printf("| %+1.12f | %3d | %+1.12f | %+1.12f | %+1.12f |\n", i.eps, i.n, i.absError, i.remTerm, i.value);
		printf("+=================+=====+=================+=================+=================+\n");
	};
};
