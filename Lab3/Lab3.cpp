#include "Lab3.h"
#include "Lab2.cpp"

numerics::vector_f64 grad_descend(func_nd func, const numerics::vector_f64& x_start, const double eps, const int max_iters) {

	numerics::vector_f64 x_0(x_start), x_i, grad;

	int i;
	for (i = 0; i < max_iters; ++i) {

		grad = numerics::vector_f64::gradient(func, x_0, eps);

		x_i = x_0 - grad;
		x_i = fibonacci(func, x_0, x_i, eps);

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
			x_i = fibonacci(func, x_0, x_i, eps);
			s_i = numerics::vector_f64::gradient(func, x_i, eps);
			omega = std::pow(s_i.magnitude(), 2) / std::pow(s_0.magnitude(), 2);
			s_0 = s_0 * omega - s_i;
			x_0 = x_i;
		}
	}

	return (x_i + x_0) * 0.5;
}

numerics::vector_f64 newton_raphson(func_nd func, const numerics::vector_f64& x_start, const double eps, const int max_iters) {

	numerics::vector_f64 x_0(x_start), x_i, grad, hess;

	int i;
	for (i = 0; i < max_iters; ++i) {

		grad = numerics::vector_f64::gradient(func, x_0, eps);
		hess = numerics::matrix_f64::invert(numerics::matrix_f64::hessian(func, x_0, eps));

		x_i = x_0 - (hess * grad);

		if (numerics::vector_f64::distance(x_i, x_0) < 2 * eps) {
			return (x_0 + x_i) * 0.5;
		}
		else {
			x_0 = x_i;
		}
	}

	return (x_0 + x_i) * 0.5;
}

template<typename T>
struct penalty_function {

public:

	using vect = numerics::numeric_vector_<T>;
	using bound_func = std::function<T(const vect&)>;

private:

	std::list<bound_func> m_boundaries;
	bound_func m_target;

public:

	penalty_function()
		: m_target([](const vect& arg) {return vect::template dot(arg, arg); }) {}

	penalty_function(const bound_func& target)
		: m_target(target) {}

	const bound_func& get_target() const {
		return m_target;
	}

	void set_target(const bound_func& func) {
		m_target = func;
	}

	void add_bound(const bound_func& func) {
		m_boundaries.push_back(func);
	}

	void del_bound(const bound_func& func) {
		m_boundaries.remove(func);
	}

	T operator()(const vect& arg) const {
		T value = m_target(arg);

		for (auto const& bound : m_boundaries) {
			value += bound(arg);
		}

		return value;
	}
};