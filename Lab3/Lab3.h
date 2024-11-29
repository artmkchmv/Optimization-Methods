#pragma once
#include <unordered_set>
#include <list>
#include "common.h"
#include "numeric_vector.h"
#include "numeric_matrix.h"

using func_nd = std::function<double(const numerics::vector_f64&)>;

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
    int penalty_type;
    T lambda;

public:
    penalty_function()
        : m_target([](const vect& arg) { return vect::template dot(arg, arg); }),
        penalty_type(0), lambda(1.0) {}

    penalty_function(const bound_func& target, int type = 0, T lambda_value = 1.0)
        : m_target(target), penalty_type(type), lambda(lambda_value) {}

    const bound_func& get_target() const {
        return m_target;
    }

    void set_target(const bound_func& func) {
        m_target = func;
    }

    void set_penalty_type(int type) {
        penalty_type = type;
    }

    int get_penalty_type() const {
        return penalty_type;
    }

    void set_lambda(T lambda_value) {
        lambda = lambda_value;
    }

    void add_bound(const bound_func& func) {
        m_boundaries.push_back(func);
    }

    void del_bound(const bound_func& func) {
        m_boundaries.remove(func);
    }

    T operator()(const vect& arg) const {
        T value = m_target(arg);

        if (penalty_type == 0 || m_boundaries.empty()) {
            return value;
        }

        T penalty = 0.0;
        if (penalty_type == 2) {
            for (const auto& bound : m_boundaries) {
                T g = bound(arg);
                if (g > 0) {
                    penalty += lambda * g * g;
                }
            }
        }
        else if (penalty_type == 1) {
            for (const auto& bound : m_boundaries) {
                T g = bound(arg);
                if (g <= 0) {
                    penalty += lambda / std::abs(g);
                }
                else {
                    return std::numeric_limits<T>::infinity();
                }
            }
        }

        return value + penalty;
    }
};

typedef penalty_function<float> penalty_f32;
typedef penalty_function<double> penalty_f64;
