#include "Lab1.h"
#include <iostream>

static double test_func1d(const double x) {
	return x * x + 2 * x + 1;
}

int main(int argc, char* argv[]) {
	std::cout << bisection(test_func1d, -3, 3) << '\n';
	std::cout << gold_ratio(test_func1d, -3, 3) << '\n';
	std::cout << fibonacci(test_func1d, -3, 3, 2e-6);
	return 0;
}