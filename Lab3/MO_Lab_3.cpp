#include "Lab3.h"
#include <iostream>

static double test_func2d(const numerics::vector_f64& args) {
	return (args[0] - 5) * args[0] + (args[1] - 3) * args[1];
}

int main(int argc, char* argv[]) {

	numerics::vector_f64 x_start = { 0, 0 };

	std::cout << "Gradient Descend method:   " << grad_descend(test_func2d, x_start) << '\n';
	std::cout << "Conjugate Gradient method: " << conjugate_grad(test_func2d, x_start) << '\n';
	std::cout << "Newton_Raphson method:     " << newton_raphson(test_func2d, x_start) << '\n';

    using vect = numerics::vector_f64;
    using bound_func = std::function<double(const vect&)>;

    penalty_f64 penalty_func_no_penalty(test_func2d, 0);

    penalty_f64 penalty_func_internal(test_func2d, 1, 1.0);

    penalty_func_internal.add_bound([](const vect& args) -> double {
        return (args[0] - 5) * args[0] + (args[1] - 3) * args[1] - 0.25;
        }); // (x - 5) * x + (y - 3) * y > 0.25

    penalty_f64 penalty_func_external(test_func2d, 2, 1.0);

    penalty_func_external.add_bound([](const vect& args) -> double {
        return args[0] - 6; // x <= 6
        });

    penalty_func_external.add_bound([](const vect& args) -> double {
        return -args[0] - 1; // x >= -1
        });

    penalty_func_external.add_bound([](const vect& args) -> double {
        return 1 - args[1]; // y >= 1
        });

    penalty_func_external.add_bound([](const vect& args) -> double {
        return 1 - args[1]; // y >= 1
        });

    std::cout << "\nPenalty function without bounds:\n";
    std::cout << "Gradient Descend method:   " << grad_descend(penalty_func_no_penalty, x_start) << '\n';
    std::cout << "Conjugate Gradient method: " << conjugate_grad(penalty_func_no_penalty, x_start) << '\n';
    std::cout << "Newton_Raphson method:     " << newton_raphson(penalty_func_no_penalty, x_start) << '\n';

    std::cout << "\nPenalty function with internal penalty:\n";
    std::cout << "Gradient Descend method:   " << grad_descend(penalty_func_internal, x_start) << '\n';
    std::cout << "Conjugate Gradient method: " << conjugate_grad(penalty_func_internal, x_start) << '\n';
    std::cout << "Newton_Raphson method:     " << newton_raphson(penalty_func_internal, x_start) << '\n';

    std::cout << "\nPenalty function with external penalty:\n";
    std::cout << "Gradient Descend method:   " << grad_descend(penalty_func_external, x_start) << '\n';
    std::cout << "Conjugate Gradient method: " << conjugate_grad(penalty_func_external, x_start) << '\n';
    std::cout << "Newton_Raphson method:     " << newton_raphson(penalty_func_external, x_start) << '\n';

	return 0;
}
