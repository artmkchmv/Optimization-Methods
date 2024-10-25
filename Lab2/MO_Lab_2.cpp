#include "Lab2.h"
#include <iostream>

static double test_func2d(const numerics::vector_f64& args) {
	return (args[0] - 5) * args[0] + (args[1] - 3) * args[1];
}

int main(int argc, char* argv[]) {

	numerics::vector_f64 x_0 = { 0, 0 };
	numerics::vector_f64 x_1 = { 5, 3 };

	std::cout << "x_0 = " << x_0 << "\nx_1 = " << x_1 << "\n";
	std::cout << bisection(test_func2d, x_0, x_1) << '\n';
	std::cout << gold_ratio(test_func2d, x_0, x_1) << '\n';
	std::cout << fibonacci(test_func2d, x_0, x_1, 2e-6) << '\n';

	numerics::vector_f64 x_start = { 0, 0 };
	std::cout << coord_descend(test_func2d, x_start) << '\n';

	return 0;
}
