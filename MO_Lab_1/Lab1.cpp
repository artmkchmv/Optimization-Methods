#include "Lab1.h"
#include <iostream>

double bisection(func_1d target_func, double lhs, double rhs, const double eps, const int max_iters) {

	if (lhs > rhs) {
		std::swap(lhs, rhs);
	}

	int iteration = 0;

	for (; iteration < max_iters && (rhs - lhs) >= 2 * eps; ++iteration) {

		const double xc = (rhs + lhs) * 0.5;

		if (target_func(xc - eps) > target_func(xc + eps)) {
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

double gold_ratio(func_1d target_func, double lhs, double rhs, const double eps, const int max_iters) {

	if (lhs > rhs) {
		std::swap(lhs, rhs);
	}

	int iteration = 0;

	double x_l = rhs - (rhs - lhs) * PSI;
	double x_r = lhs + (rhs - lhs) * PSI;
	double f_l = target_func(x_l);
	double f_r = target_func(x_r);

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

double fibonacci(func_1d target_func, double lhs, double rhs, const double eps) {

	if (lhs > rhs) {
		std::swap(lhs, rhs);
	}

	int iteration = 0;
	int iterations = 0;
	double f_n = 1;
	double f_n_1 = 1;
	double ratio = (rhs - lhs) / eps;

	fib_pair(ratio, f_n, f_n_1, iterations);

	double x_l = lhs + (rhs - lhs) * ((f_n_1 - f_n) / f_n_1);
	double x_r = lhs + (rhs - lhs) * (f_n / f_n_1);
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