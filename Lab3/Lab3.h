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

typedef penalty_function<float> penalty_f32;
typedef penalty_function<double> penalty_f64;
