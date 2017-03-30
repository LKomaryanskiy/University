#include "Approximation.h"

Approximation::Approximation(func_t source_func, double a, double b, double eps, unsigned int start_n, bool print_log)
	: m_func(source_func), m_a(a), m_b(b), m_eps(eps), c_start_n(start_n), m_print_log(print_log)
{
	m_is_calculated = false;
	m_n = c_start_n;
};

std::vector<double> Approximation::Calculate()
{
	if (m_print_log)
	{
		printf("Start calculations: a = %+2.1e, b = %+2.1e, eps = %2e\n", m_a, m_b, m_eps);
	}

	if (m_is_calculated)
		return m_polynomial;

	CreateMatrix();
	SolveMatrix();
	double error = GetError();

	while (error >= m_eps)
	{
		if (m_print_log)
		{
			printf("N = %d, Current error = %3.10e\n", m_n, error);
		}

		++m_n;
		CreateMatrix();
		SolveMatrix();
		error = GetError();
	}
	if (m_print_log)
	{
		printf("N = %d, Current error = %3.10e\n", m_n, error);
	}

	m_is_calculated = true;
	return m_polynomial;
};

void Approximation::SaveToFile(const std::string& file_path_x, const std::string& file_path_y)
{
	if (!m_is_calculated)
		throw std::exception("Can't save into the files without calculations\n");

	std::ofstream x_file(file_path_x);
	if (!x_file.is_open())
		throw std::exception("Can't create file with X\n");

	std::ofstream y_file(file_path_y);
	if (!y_file.is_open())
		throw std::exception("Can't create file with Y\n");

	double h = sqrt(m_eps);
	unsigned long int n((m_b - m_a) / h);
	h = (m_b - m_a) / double(n);

	for (unsigned int i = 0; i <= n; ++i)
	{
		x_file << (m_a + i * h) << std::endl;
		y_file << CalculatePolynomial(m_a + i * h) << std::endl;
	}
	x_file.close();
	y_file.close();
};

double Approximation::LegandrePoly(double x, int n)
{
	if (n == 0)
		return 1.0;
	if (n == 1)
		return x;

	double P;
	double P0 = 1;
	double P1 = x;
	for (int i = 2; i <= n; ++i)
	{
		P = (((2 * i) * x * P1) - (i * P0)) / (i + 1.0);
		P0 = P1;
		P1 = P;
	}

	return P;
};

double Approximation::IntegrateFreeMember(int n, double h)
{
	//Recalc h
	unsigned long int steps((m_b - m_a) / h);
	h = (m_b - m_a) / double(steps);

	double sum = 0.0;
	const double half_h = h / 2.0;
	for (unsigned int i = 0; i < steps; ++i)
	{
		sum += m_func(m_a + h * i) * LegandrePoly(m_a + h * i, n) +
			4.0 * m_func(m_a + h * i + half_h) * LegandrePoly(m_a + h * i + half_h, n) +
			m_func(m_a + h * (i + 1.0)) * LegandrePoly(m_a + h * (i + 1.0), n);
	}

	return (h / 6.0) * sum;
};

double Approximation::IntegrateCoeff(int n1, int n2, double h)
{
	//Recalc h
	unsigned long int steps((m_b - m_a) / h);
	h = (m_b - m_a) / double(steps);

	double sum = 0.0;
	const double half_h = h / 2.0;
	for (unsigned int i = 0; i < steps; ++i)
	{
		sum += LegandrePoly(m_a + h * i, n1) * LegandrePoly(m_a + h * i, n2) +
			4.0 * LegandrePoly(m_a + h * i + half_h, n1) * LegandrePoly(m_a + h * i + half_h, n2) +
			LegandrePoly(m_a + h * (i + 1.0), n1) * LegandrePoly(m_a + h * (i + 1.0), n2);
	}

	return (h / 6.0) * sum;
};

double Approximation::CalculateFreeMember(int n)
{
	double h = std::sqrt(std::sqrt(m_eps));
	double result = IntegrateFreeMember(n, h);
	h /= 2.0;
	double refined_result = IntegrateFreeMember(n, h);
	//Percentage error
	while (m_eps <= std::fabs((result - refined_result) / (15.0 * result)))
	{
		result = refined_result;
		h /= 2.0;
		refined_result = IntegrateFreeMember(n, h);
	}

	return refined_result;
};

double Approximation::CalculateCoeff(int n1, int n2)
{
	double h = std::sqrt(std::sqrt(m_eps));
	double result = IntegrateCoeff(n1, n2, h);
	h /= 2.0;
	double refined_result = IntegrateCoeff(n1, n2, h);
	//Percentage error
	while (m_eps <= std::fabs((result - refined_result) / (15.0 * result)))
	{
		result = refined_result;
		h /= 2.0;
		refined_result = IntegrateCoeff(n1, n2, h);
	}

	return refined_result;
};

double Approximation::CalculatePolynomial(double x)
{
	double value = 0.0;
	for (unsigned int i = 0; i < m_polynomial.size(); ++i)
		value += m_polynomial[i] * LegandrePoly(x, i);

	return value;
};

double Approximation::GetError()
{
	double value;
	double result = 0.0;
	double h = sqrt(m_eps);
	unsigned long int n((m_b - m_a) / h);
	h = (m_b - m_a) / double(n);

	for (unsigned long int i = 0; i <= n; ++i)
	{
		value = m_func(m_a + h * i) - CalculatePolynomial(m_a + h * i);
		result += value * value;
	}

	return sqrt(result / double(n + 1));
};

void Approximation::CreateMatrix()
{
	m_matrix.resize(m_n);
	m_matrix[m_n - 1].resize(m_n + 1);
	
	for (unsigned int i = 0; i < m_n; ++i)
	{
		m_matrix[i].resize(m_n + 1);
		for (unsigned int j = 0; j < m_n; ++j)
		{
			m_matrix[i][j] = CalculateCoeff(i, j);
		}
		m_matrix[i][m_n] = CalculateFreeMember(i);
	}
	
};

void Approximation::SolveMatrix()
{
	std::vector<std::vector<double>> matrix = m_matrix;

	//Direct path
	for (unsigned int i = 0; i < m_n; ++i)
	{
		double dev_value = matrix[i][i];

		if (dev_value == 0.0)
			return;

		for (unsigned int j = 0; j <= m_n; ++j)
		{
			matrix[i][j] /= dev_value;
		}

		unsigned int k = i + 1;
		while (k < m_n)
		{
			double coof = matrix[k][i];
			for (unsigned int j = i; j <= m_n; ++j)
			{
				matrix[k][j] /= coof;
				matrix[k][j] -= matrix[i][j];
			}
			k++;
		}

	}

	//Reverse path
	m_polynomial = std::vector<double>(m_n, 1.0);
	for (int i = m_n - 1; i >= 0; --i)
	{
		for (int j = m_n - 1; j > i; --j)
			matrix[i][m_n] -= matrix[i][j] * m_polynomial[j];
		m_polynomial[i] = matrix[i][m_n] / m_polynomial[i];
	}
};