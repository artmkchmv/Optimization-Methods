//Lab. 2

#include <iostream>
#include "common.h"
#include "numeric_vector.h"

typedef double(*func_id)(const numerics::vector_f64);
numerics::vector_f64 bisect(func_id target_func, numerics::vector_f64& lhs, numerics::vector_f64& rhs, const double eps = 1e-6, const int max_iters = 100);
numerics::vector_f64 gold(func_id target_func, numerics::vector_f64& lhs, numerics::vector_f64& rhs, const double eps = 1e-6, const int max_iters = 100);
numerics::vector_f64 fib(func_id target_func, numerics::vector_f64& lhs, numerics::vector_f64& rhs, const double eps = 1e-6);

numerics::vector_f64 bisect(func_id target_func, numerics::vector_f64& lhs, numerics::vector_f64& rhs, const double eps, const int max_iters) {

	numerics::vector_f64 xc;
	numerics::vector_f64 direct = numerics::vector_f64::direction(lhs, rhs);
	int iteration = 0;

	for (; iteration < max_iters && (rhs - lhs) >= 2 * eps; ++iteration) {

		xc = (rhs + lhs) * 0.5;

		if (target_func(xc - direct) > target_func(xc + direct)) {
			lhs = xc;
		}
		else {
			rhs = xc;
		}
	}

	std::cout << "bisect::range : " << rhs - lhs << '\n';
	std::cout << "bisect::probs : " << 2 * iteration << '\n';

	return (rhs + lhs) * 0.5;
}

numerics::vector_f64 gold(func_id target_func, numerics::vector_f64& lhs, numerics::vector_f64& rhs, const double eps, const int max_iters) {

	numerics::vector_f64 x_l = rhs - (rhs - lhs) * PSI;
	numerics::vector_f64 x_r = lhs + (rhs - lhs) * PSI;
	double f_l = target_func(x_l);
	double f_r = target_func(x_r);
	int iteration = 0;

	for (; iteration < max_iters && (rhs - lhs) >= 2 * eps; ++iteration) {

		if (f_l > f_r) {
			lhs = x_l;
			x_l = x_r;
			f_l = f_r;
			x_r = lhs + (rhs - lhs) * PSI;
			f_r = target_func(x_r);
		}
		else {
			rhs = x_r;
			x_r = x_l;
			f_r = f_l;
			x_l = rhs - (rhs - lhs) * PSI;
			f_l = target_func(x_l);
		}
	}

	std::cout << "gold::range : " << rhs - lhs << '\n';
	std::cout << "gold::probs : " << iteration + 2 << '\n';

	return (rhs + lhs) * 0.5;
}

static void fib_pair(double ratio, double& f_n, double& f_n_1, int& iterations) {

	double temp = 0;

	while (f_n_1 < ratio) {

		++iterations;
		temp = f_n;
		f_n = f_n_1;
		f_n_1 += temp;
	}
}

static void fib_prev(double& f_n, double& f_n_1) {
	double temp = f_n_1 - f_n;
	f_n_1 = f_n;
	f_n = temp;
}

numerics::vector_f64 fib(func_id target_func, numerics::vector_f64& lhs, numerics::vector_f64& rhs, const double eps) {

	int iteration = 0;
	int iterations = 0;
	double f_n = 1;
	double f_n_1 = 1;
	double ratio = numerics::vector_f64::distance(lhs, rhs) / eps;

	fib_pair(ratio, f_n_1, f_n, iterations);

	numerics::vector_f64 x_l = lhs + (rhs - lhs) * ((f_n_1 - f_n) / f_n_1);
	numerics::vector_f64 x_r = lhs + (rhs - lhs) * (f_n / f_n_1);
	double f_l = target_func(x_l);
	double f_r = target_func(x_r);

	for (; iteration < iterations; ++iteration) {

		fib_prev(f_n, f_n_1);

		if (f_l > f_r) {
			lhs = x_l;
			x_l = x_r;
			f_l = f_r;
			x_r = lhs + (rhs - lhs) * (f_n / f_n_1);
			f_r = target_func(x_r);
		}
		else {
			rhs = x_r;
			x_r = x_l;
			f_r = f_l;
			x_l = lhs + (rhs - lhs) * ((f_n_1 - f_n) / f_n_1);
			f_l = target_func(x_l);
		}
	}

	std::cout << "fib::range : " << rhs - lhs << '\n';
	std::cout << "fib::probs : " << iteration + 2 << '\n';

	return (rhs + lhs) * 0.5;
}
