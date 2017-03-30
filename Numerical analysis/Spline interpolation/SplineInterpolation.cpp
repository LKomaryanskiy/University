#include "SplineInterpolation.h"

SplineInterpolation::SplineInterpolation(func_t func, double a, double b, unsigned int n) :
	m_func(func), m_a(a), m_b(b), m_n(n) 
{
	if (m_a >= m_b)
	{
		std::swap(m_a, m_b);
	}
	if (m_n == 0)
	{
		m_n = 1;
	}

	m_is_need_update = true;
};

std::vector<vector2d> SplineInterpolation::Calculate(unsigned int amount_of_points)
{
	const double h = (m_b - m_a) / double(amount_of_points - 1);
	
	FillSplineVector();

	m_points = std::vector<vector2d>(amount_of_points);

	for (unsigned int i = 0; i < amount_of_points; ++i)
	{
		m_points[i] = GetSplinePlot(m_a + i * h);
	}

	m_is_need_update = false;
	return m_points;
};

void SplineInterpolation::SaveToFile(std::string file_path)
{
	if (m_is_need_update)
	{
		throw std::exception("Need update the plots\n");
	}

	std::ofstream file(file_path);
	if (!file.is_open())
	{
		throw std::exception("Can't create file\n");
	}

	const double h = (m_b - m_a) / double(m_points.size() + 1);
	for (unsigned int i = 0; i < m_points.size(); ++i)
	{
		file << (m_points[i].x) << ";" << (m_points[i].y) << std::endl;
	}
	file.close();
}

void SplineInterpolation::SetA(double a)
{
	if (a >= m_b)
	{
		throw std::exception("Error: a must be less then b\n");
	}
	m_a = a;
	m_is_need_update = true;
};

void SplineInterpolation::SetB(double b)
{
	if (m_a >= b)
	{
		throw std::exception("Error: b must be more then a\n");
	}
	m_b = b;
	m_is_need_update = true;
};

void SplineInterpolation::SetN(unsigned int N)
{
	if (N == 0)
	{
		throw std::exception("Error: N can't apply a zero value\n");
	}
	m_n = N;
	m_is_need_update = true;
};

std::vector<std::vector<double>> SplineInterpolation::CreateMatrix()
{
	std::vector<std::vector<double>> matrix = std::vector<std::vector<double>>(m_n, std::vector<double>((m_n + 1), 0.0));
	const double h = (m_b - m_a) / double(m_n - 1);
	matrix[0][0] = 1.0;
	matrix[m_n - 1][m_n - 1] = 1.0;
	
	for (unsigned int i = 1; i < m_n - 1; ++i)
	{
		matrix[i][i] = 4.0 * h;
		matrix[i][i - 1] = h;
		matrix[i][i + 1] = h;
		matrix[i][m_n] = (6.0 * (m_func(m_a + (i + 1.0) * h) - 2 * m_func(m_a + i * h) + m_func(m_a + (i - 1.0) * h))) / h;
	}

	return matrix;
};

std::vector<double> SplineInterpolation::SolveMatrix(std::vector<std::vector<double>> matrix)
{
	for (unsigned int i = 0; i < m_n; ++i)
	{
		double elem = matrix[i][i];
		for (unsigned int j = i; j <= m_n; ++j)
		{
			matrix[i][j] /= elem;
		}

		for (unsigned int j = 0; j < m_n; ++j)
		{
			if (i != j)
			{
				const double factor = matrix[j][i];
				for (unsigned int k = i; k <= m_n; ++k)
				{
					matrix[j][k] -= matrix[i][k] * factor;
				}
			}
		}
	}

	std::vector<double> roots = std::vector<double>(m_n);
	for (int i = 0; i < m_n; ++i)
	{
		roots[i] = matrix[i][m_n];
	}

	return roots;
};

void SplineInterpolation::FillXField()
{
	const double h = (m_b - m_a) / double(m_n - 1);
	for (unsigned int i = 0; i < m_n; ++i)
	{
		m_spline[i].x = m_a + h * i;
	}
};

void SplineInterpolation::FillAField()
{
	for (unsigned int i = 0; i < m_n; ++i)
	{
		m_spline[i].a = m_func(m_spline[i].x);
	}
};

void SplineInterpolation::FillBField()
{
	const double h = (m_b - m_a) / double(m_n - 1);
	m_spline[0].b = 0.0;
	for (unsigned int i = 1; i < m_n; ++i)
	{
		m_spline[i].b = (h / 2.0) * m_spline[i].c - ((h * h) / 6.0) * m_spline[i].d + (m_func(m_spline[i].x) - m_func(m_spline[i - 1].x)) / h;
	}
};

void SplineInterpolation::FillCField()
{
	m_spline[0].c = 0.0;
	std::vector<double> vector_c = SolveMatrix(CreateMatrix());
	for (unsigned int i = 1; i < m_n; ++i)
	{
		m_spline[i].c = vector_c[i];
	}
};

void SplineInterpolation::FillDField()
{
	m_spline[0].d = 0.0;
	const double h = (m_b - m_a) / double(m_n - 1);
	for (unsigned int i = 1; i < m_n; ++i)
	{
		m_spline[i].d = (m_spline[i].c - m_spline[i - 1].c) / h;
	}
};

void SplineInterpolation::FillSplineVector()
{
	m_spline = std::vector<spline_t>(m_n);
	FillXField();
	FillCField();
	FillDField();
	FillBField();
	FillAField();
};

vector2d SplineInterpolation::GetSplinePlot(double x)
{
	unsigned int i = 0;
	while (x > m_spline[i].x && i < m_n)
	{
		++i;
	}
	vector2d ret_value;
	ret_value.x = x;
	const double delta = x - m_spline[i].x;
	ret_value.y = m_spline[i].a + m_spline[i].b * delta + (m_spline[i].c / 2.0) * delta * delta + (m_spline[i].d / 6.0) * delta * delta * delta;
	return ret_value;
};