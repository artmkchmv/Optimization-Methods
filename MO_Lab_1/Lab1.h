#pragma once
#include <cmath>

const double PSI = 2 / (1 + sqrt(5));

typedef double(*func_1d)(const double);

double bisection(func_1d target_func, double lhs, double rhs, const double eps = 1e-6, const int max_iters = 100);

double gold_ratio(func_1d target_func, double lhs, double rhs, const double eps = 1e-6, const int max_iters = 100);

double fibonacci(func_1d target_func, double lhs, double rhs, const double eps = 1e-6);

void fib_prev(double& f_n, double& f_n_1);
void fib_pair(double ratio, double& f_n, double& f_n_1, int& iterations);