#include "Lab2.h"

numerics::vector_f64 bisection(func_nd target_func, numerics::vector_f64& left, numerics::vector_f64& right, const double eps, const int max_iters) {

	numerics::vector_f64 xc, lhs(left), rhs(right);
	numerics::vector_f64 direct = numerics::vector_f64::direction(lhs, rhs) * eps;
	int iteration = 0;

	for (; iteration < max_iters && numerics::vector_f64::distance(lhs, rhs) >= 2 * eps; ++iteration) {

		xc = (rhs + lhs) * 0.5;

		if (target_func(xc - direct) > target_func(xc + direct)) {
			lhs = xc;
		}
		else {
			rhs = xc;
		}
	}

	std::cout << "bisect::range : " << numerics::vector_f64::distance(lhs, rhs) << '\n';
	std::cout << "bisect::probs : " << 2 * iteration << '\n';

	return (rhs + lhs) * 0.5;
}

numerics::vector_f64 gold_ratio(func_nd target_func, numerics::vector_f64& left, numerics::vector_f64& right, const double eps, const int max_iters) {

	int iteration = 0;

	numerics::vector_f64 lhs(left), rhs(right);
	numerics::vector_f64 x_l = rhs - (rhs - lhs) * PSI;
	numerics::vector_f64 x_r = lhs + (rhs - lhs) * PSI;
	double f_l = target_func(x_l);
	double f_r = target_func(x_r);
	double a = numerics::vector_f64::distance(lhs, rhs);
	for (; iteration < max_iters && numerics::vector_f64::distance(lhs, rhs) > 2 * eps; ++iteration) {

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

	std::cout << "gold::range : " << numerics::vector_f64::distance(lhs, rhs) << '\n';
	std::cout << "gold::probs : " << iteration + 2 << '\n';

	return (rhs + lhs) * 0.5;
}

void fib_pair(double ratio, double& f_n, double& f_n_1, int& iterations) {

	double temp = 0;

	while (f_n_1 < ratio) {

		++iterations;
		temp = f_n;
		f_n = f_n_1;
		f_n_1 += temp;
	}
}

void fib_prev(double& f_n, double& f_n_1) {
	double temp = f_n_1 - f_n;
	f_n_1 = f_n;
	f_n = temp;
}

numerics::vector_f64 fibonacci(func_nd target_func, numerics::vector_f64& left, numerics::vector_f64& right, const double eps) {

	numerics::vector_f64 lhs(left), rhs(right);
	int iteration = 0;
	int iterations = 0;
	double f_n = 1;
	double f_n_1 = 1;
	double ratio = numerics::vector_f64::distance(lhs, rhs) / eps;

	fib_pair(ratio, f_n, f_n_1, iterations);

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

	std::cout << "fib::range : " << numerics::vector_f64::distance(lhs, rhs) << '\n';
	std::cout << "fib::probs : " << iteration + 2 << '\n';

	return (rhs + lhs) * 0.5;
}

numerics::vector_f64 coord_descend(func_nd target_func, const numerics::vector_f64& x_start, const double eps, const int max_iters) {

	numerics::vector_f64 x_l(x_start), x_r(x_start);
	double y_l, y_r, x_i, step = 1;
	int coord_id, opt_coord_n = 0;

	int i;

	for (i = 0; i < max_iters; i++) {

		coord_id = i % x_l.size();

		x_r[coord_id] -= eps;
		y_l = target_func(x_r);

		x_r[coord_id] += 2 * eps;
		y_r = target_func(x_r);

		x_r[coord_id] -= eps;

		if (y_l > y_r) {
			x_r[coord_id] += step;
		}
		else {
			x_r[coord_id] -= step;
		}

		x_i = x_l[coord_id];
		std::streambuf* temp_buf = std::cout.rdbuf(nullptr);
		x_r = fibonacci(target_func, x_l, x_r, eps);
		std::cout.rdbuf(temp_buf);
		x_l = x_r;

		if (numerics::vector_f64::distance(x_l, x_r) < 2 * eps) {
	
			std::cout << "per coord_descend::probs : " << i + 1 << '\n';

			return x_l;
		}

		x_l = x_r;
	}

	return x_l;
}
