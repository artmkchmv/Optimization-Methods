#include "Lab3.h"
#include "Lab2.cpp"

numerics::vector_f64 grad_descend(func_nd func, const numerics::vector_f64& x_start, const double eps, const int max_iters) {

	numerics::vector_f64 x_0(x_start), x_i, grad;

	int i;
	for (i = 0; i < max_iters; ++i) {

		grad = numerics::vector_f64::gradient(func, x_0, eps);

		x_i = x_0 - grad;
		std::streambuf* temp_buf = std::cout.rdbuf(nullptr);
		x_i = fibonacci(func, x_0, x_i, eps);
		std::cout.rdbuf(temp_buf);

		if (numerics::vector_f64::distance(x_i, x_0) < 2 * eps) {
			return (x_0 + x_i) * 0.5;
		}
		else {
			x_0 = x_i;
		}
	}

	return (x_i + x_0) * 0.5;
}

numerics::vector_f64 conjugate_grad(func_nd func, const numerics::vector_f64& x_start, const double eps, const int max_iters) {

	numerics::vector_f64 x_0(x_start), x_i, s_0 = (-1.0) * numerics::vector_f64::gradient(func, x_0, eps), s_i;
	double omega;

	int i;
	for (i = 0; i < max_iters; ++i) {

		x_i = x_0 + s_0;

		if (numerics::vector_f64::distance(x_i, x_0) < 2 * eps) {
			return (x_0 + x_i) * 0.5;
		}
		else {
			std::streambuf* temp_buf = std::cout.rdbuf(nullptr);
			x_i = fibonacci(func, x_0, x_i, eps);
			std::cout.rdbuf(temp_buf);
			s_i = numerics::vector_f64::gradient(func, x_i, eps);
			omega = std::pow(s_i.magnitude(), 2) / std::pow(s_0.magnitude(), 2);
			s_0 = s_0 * omega - s_i;
			x_0 = x_i;
		}
	}

	return (x_i + x_0) * 0.5;
}

numerics::vector_f64 newton_raphson(func_nd func, const numerics::vector_f64& x_start, const double eps, const int max_iters) {

	numerics::vector_f64 x_0(x_start), x_i, grad;
	numerics::matrix_f64 hess;

	int i;
	for (i = 0; i < max_iters; ++i) {

		grad = numerics::vector_f64::gradient(func, x_0, eps);
		hess = numerics::matrix_f64::hessian(func, x_0, eps);

		x_i = x_0 - (numerics::matrix_f64::invert(hess) * grad);

		if (numerics::vector_f64::distance(x_i, x_0) < 2 * eps) {
			return (x_0 + x_i) * 0.5;
		}
		else {
			x_0 = x_i;
		}
	}

	return (x_0 + x_i) * 0.5;
}
