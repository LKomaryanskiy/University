#include "MatrixSolver.h"


double m_norm(std::vector<std::vector<double>> matrix)
{
	double norm = 0.0;
	const unsigned int size = matrix.size();
	for (unsigned int i = 0; i < size; ++i)
	{
		double sum = 0.0;
		for (unsigned int j = 1; j < size; ++j)
		{
			sum += fabs(matrix[i][j]);
		}
		if (norm < sum)
		{
			norm = sum;
		}
	}

	return norm;
};

std::vector<double> direct_iteration(std::vector<std::vector<double>> matrix, double eps)
{
	const int amount_of_roots = matrix.size();
	std::vector<double> roots(amount_of_roots, 0.0);
	//Roots for iterations
	std::vector<double> tmp_roots(amount_of_roots, 0.0);

	const double q = m_norm(matrix);
	if (q >= 1)
		throw std::exception("M Norm > !\n");

	const double precision = ((1.0 - q) / q) * eps;
	double curr_norm = 1.0;

	while (curr_norm > precision)
	{
		for (int j = 0; j < amount_of_roots; ++j)
		{
			tmp_roots[j] = matrix[j][0];
			for (int k = 0; k < amount_of_roots; ++k)
			{
				tmp_roots[j] += roots[k] * matrix[j][k + 1];
			}
		}
		curr_norm = 0.0;
		for (unsigned int i = 0; i < amount_of_roots; ++i)
		{
			curr_norm += fabs(roots[i] - tmp_roots[i]);
		}
		roots = tmp_roots;

	}

	return roots;
};


std::vector<double> gaussian_elimination(std::vector<std::vector<double>> matrix)
{
	const int amount_of_roots = matrix.size();

	//Direct path
	for (int i = 0; i < amount_of_roots; ++i)
	{
		double dev_value = matrix[i][i];

		if (dev_value == 0.0)
			return std::vector<double>();

		for (int j = 0; j <= amount_of_roots; ++j)
		{
			matrix[i][j] /= dev_value;
		}

		int k = i + 1;
		while (k < amount_of_roots)
		{
			double coof = matrix[k][i];
			for (int j = i; j <= amount_of_roots; ++j)
			{
				matrix[k][j] /= coof;
				matrix[k][j] -= matrix[i][j];
			}
			k++;
		}

	}
	
	//Reverse path
	std::vector<double> roots(amount_of_roots, 1.0);
	for (int i = amount_of_roots - 1; i >= 0; --i)
	{
		for (int j = amount_of_roots - 1; j > i; --j)
			matrix[i][amount_of_roots] -= matrix[i][j] * roots[j];
		roots[i] = matrix[i][amount_of_roots] / roots[i];
	}

	return roots;
};

std::vector<double> complete_pivoting(std::vector<std::vector<double>> matrix)
{
	const int amount_of_roots = matrix.size();
	std::vector<double> roots(amount_of_roots, 0.0);
	std::vector<std::vector<double>> triangle_matrix;
	std::vector<int> deleted_columns;
	
	for (int iteration = 0; iteration < amount_of_roots; ++iteration)
	{
		double max_value = 0.0;
		int i_pos = 0;
		int j_pos = 0;

		for (int i = 0; i < amount_of_roots; ++i)
		{
			for (int j = 0; j < amount_of_roots; ++j)
			{
				if (fabs(matrix[i][j]) > max_value)
				{
					max_value = fabs(matrix[i][j]);
					i_pos = i;
					j_pos = j;
				}
			}
		}

		deleted_columns.push_back(j_pos);
		triangle_matrix.push_back(matrix[i_pos]);

		std::vector<double> vector_m(amount_of_roots, 0.0);
		for (int i = 0; i < amount_of_roots; ++i)
		{
			vector_m[i] = -matrix[i][j_pos] / matrix[i_pos][j_pos];
		}

		for (int i = 0; i < amount_of_roots; ++i)
		{
			if (i != i_pos)
			{
				for (int j = 0; j < amount_of_roots + 1; ++j)
				{
					matrix[i][j] += matrix[i_pos][j] * vector_m[i];
				}
			}
		}

		//'Delete' max column and row with max element
		for (int i = 0; i < amount_of_roots; ++i)
		{
			matrix[i][j_pos] = 0.0;
			matrix[i_pos][i] = 0.0;
		}
	}

	//Reverse path
	for (int i = amount_of_roots - 1; i >=0; --i)
	{
		for (int j = amount_of_roots - 1; j >= 0; --j)
		{
			if (j != deleted_columns[i])
			{
				triangle_matrix[i][amount_of_roots] -= triangle_matrix[i][j] * roots[j];
			}
		}
		roots[deleted_columns[i]] = triangle_matrix[i][amount_of_roots] / triangle_matrix[i][deleted_columns[i]];
	}

	return roots;
};