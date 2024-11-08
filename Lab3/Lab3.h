#pragma once
#include <unordered_set>
#include <list>
#include "common.h"
#include "numeric_vector.h"
#include "numeric_matrix.h"

typedef double(*func_nd)(const numerics::vector_f64&);

numerics::vector_f64 grad_descend(func_nd func, const numerics::vector_f64& x_start, const double eps = 1e-6, const int max_iters = 100);

numerics::vector_f64 conjugate_grad(func_nd func, const numerics::vector_f64& x_start, const double eps = 1e-6, const int max_iters = 100);

numerics::vector_f64 newton_raphson(func_nd func, const numerics::vector_f64& x_start, const double eps = 1e-6, const int max_iters = 100);

template<typename T>
struct penalty_function;

typedef penalty_function<float> penalty_f32;
typedef penalty_function<double> penalty_f64;