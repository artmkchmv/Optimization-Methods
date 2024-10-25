#pragma once
#include "common.h"
#include "numeric_vector.h"

typedef double(*func_nd)(const numerics::vector_f64&);

numerics::vector_f64 bisection(func_nd target_func, numerics::vector_f64& lhs, numerics::vector_f64& rhs, const double eps = 1e-6, const int max_iters = 100);

numerics::vector_f64 gold_ratio(func_nd target_func, numerics::vector_f64& lhs, numerics::vector_f64& rhs, const double eps = 1e-6, const int max_iters = 100);

numerics::vector_f64 fibonacci(func_nd target_func, numerics::vector_f64& lhs, numerics::vector_f64& rhs, const double eps = 1e-6);

void fib_pair(double ratio, double& f_n, double& f_n_1, int& iterations);
void fib_prev(double& f_n, double& f_n_1);

numerics::vector_f64 coord_descend(func_nd target_func, const numerics::vector_f64& x_start, const double eps = 1e-6, const int max_iters = 100);