#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <math.h>
#include <stdio.h>


//Source function type
typedef double(*func_t)(double x);

class Approximation
{
public:
	Approximation(func_t source_func = [](double x) {return x; }, double a = -1.0, double b = 1.0, double eps = 1e-2, unsigned int start_n = 30, bool print_log = false);
	std::vector<double> Calculate();
	void SaveToFile(const std::string& file_path_x = "x.txt", const std::string& file_path_y = "y.txt");

	double GetA() { return m_a; };
	double GetB() { return m_b; };
	double GetEps() { return m_eps; };
	func_t GetFunc() { return m_func; };

	void SetA(double a) { m_is_calculated = false; m_a = a; };
	void SetB(double b) { m_is_calculated = false; m_b = b; };
	void SetEps(double eps) { m_is_calculated = false; m_eps = eps; };
	void SetFunc(func_t func) { m_is_calculated = false; m_func = func; };

	~Approximation() {};
private:
	std::vector<double> m_polynomial;
	unsigned int m_n;
	bool m_is_calculated;
	bool m_print_log;
	std::vector<std::vector<double>> m_matrix;

	func_t m_func;
	double m_a;
	double m_b;
	double m_eps;
	const unsigned int c_start_n;

	double LegandrePoly(double x, int n);
	//Use Simpson rule for integration
	double IntegrateFreeMember(int n, double h);
	double IntegrateCoeff(int n1, int n2, double h);
	//Refined calculation for more presition
	double CalculateFreeMember(int n);
	double CalculateCoeff(int n1, int n2);

	double CalculatePolynomial(double x);
	double GetError();

	void CreateMatrix();

	//Use Gaussian elimination for solving
	void SolveMatrix();
	//Forebidden constructors
	Approximation() = delete;
	Approximation(Approximation&) = delete;
	Approximation& operator=(Approximation&) = delete;
};