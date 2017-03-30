#pragma once
#include <vector>

std::vector<double> direct_iteration(std::vector<std::vector<double>> matrix, double eps = 0.001);

//For 5 laboratory work
std::vector<double> gaussian_elimination(std::vector<std::vector<double>> matrix);

std::vector<double> complete_pivoting(std::vector<std::vector<double>> matrix);