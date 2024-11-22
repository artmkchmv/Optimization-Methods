#include "Lab3.h"
#include <iostream>

static double test_func2d(const numerics::vector_f64& args) {
	return (args[0] - 5) * args[0] + (args[1] - 3) * args[1];
}

int main(int argc, char* argv[]) {

	numerics::vector_f64 x_start = { 0, 0 };

	std::cout << "Gradient Descend method: " << grad_descend(test_func2d, x_start) << '\n';
	std::cout << "Conjugate Gradient method: " << conjugate_grad(test_func2d, x_start) << '\n';
	std::cout << "Newton_Raphson method: " << newton_raphson(test_func2d, x_start) << '\n';

	using vect = numerics::vector_f64;
	using bound_func = std::function<double(const vect&)>;

	bound_func target_function = [](const vect& args) {
		return (args[0] - 1) * (args[0] - 1) + (args[1] - 1) * (args[1] - 1);
		};

	penalty_f64 penalty_func(target_function);

	penalty_func.add_bound([](const vect& args) -> double {
		return args[0] < 0 ? 100.0 : 0.0; // Штраф, если x < 0
		});

	penalty_func.add_bound([](const vect& args) -> double {
		return args[1] < 0 ? 100.0 : 0.0; // Штраф, если y < 0
		});

	penalty_func.add_bound([](const vect& args) -> double {
		return args[0] > 10 ? 100.0 : 0.0; // Штраф, если x > 10
		});

	penalty_func.add_bound([](const vect& args) -> double {
		return args[1] > 10 ? 100.0 : 0.0; // Штраф, если y > 10
		});

	std::cout << "Penalty function method: " << penalty_func(x_start) << '\n';

	return 0;
}
