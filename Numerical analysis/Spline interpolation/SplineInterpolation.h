#pragma once
#include <math.h>
#include <vector>
#include <string>
#include <fstream>


typedef double(*func_t)(double x);
struct spline_t
{
	double a;
	double b;
	double c;
	double d;
	double x;
};

struct vector2d
{
	double x;
	double y;
};

class SplineInterpolation
{
public:
	SplineInterpolation(func_t func = [](double x) { return x; }, double a = 0.0, double b = 1.0, unsigned int n = 100);
	std::vector<vector2d> Calculate(unsigned int amount_of_points = 100);
	void SaveToFile(std::string file_path = "plots.csv");
	~SplineInterpolation() {};

	double GetA() { return m_a; };
	double GetB() { return m_b; };
	unsigned int GetN() { return m_n; };

	void SetA(double a);
	void SetB(double b);
	void SetN(unsigned int N);

private:
	func_t m_func;
	double m_a;
	double m_b;
	unsigned int m_n;
	std::vector<spline_t> m_spline;
	std::vector<vector2d> m_points;
	bool	m_is_need_update;

	std::vector<std::vector<double>> CreateMatrix();
	//Use Gaussian elimination 
	std::vector<double> SolveMatrix(std::vector<std::vector<double>> matrix);

	void FillXField();
	void FillAField();
	void FillBField();
	void FillCField();
	void FillDField();
	void FillSplineVector();
	vector2d GetSplinePlot(double x);

	//Forebidden constructors
	SplineInterpolation() = delete;
	SplineInterpolation(SplineInterpolation&) = delete;
	SplineInterpolation& operator=(SplineInterpolation&) = delete;
};