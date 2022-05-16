#ifndef LAB1_3_SYSTEM_SOLVER_HPP
#define LAB1_3_SYSTEM_SOLVER_HPP

#include <iostream>
#include <math.h>
#include "matrix.hpp"

static const double EPS = 0.01;

template<class T>
class system_solver {
public:
    system_solver(size_t, T);
    std::vector<T> fixed_point_iterations(size_t &);
    std::vector<T> seidel(size_t &);
    bool check_solution(std::vector<T>);
    void check_norm();
private:
    std::pair<matrix<T>, std::vector<T>> jacobi_method();
    T norm_vec(std::vector<T>);
    T norm_matrix(matrix<T>);
    T sum_abs(std::vector<T>);
    matrix<T> a;
    std::vector<T> b;
    T eps;
    T __norm_alpha;
};


// Implementation

// Constructor
template<class T>
system_solver<T>::system_solver(size_t n, T epsilon): a(n), b(n) {
    a.push_matrix();
    for (size_t i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    eps = epsilon;
}

// Norms
template<class T>
T system_solver<T>::norm_vec(std::vector<T> vector) {
    T max_vector = std::abs(vector[0]);
    for (size_t i = 1; i < vector.size(); i++) {
        if (std::abs(vector[i]) > max_vector) max_vector = abs(vector[i]);
    }
    return max_vector;
}

template<class T>
T system_solver<T>::norm_matrix(matrix<T> matrix) {
    T max_matrix = sum_abs(matrix[0]);
    for (size_t i = 1; i < matrix.size(); i++) {
        if (sum_abs(matrix[i]) > max_matrix) max_matrix = sum_abs(matrix[i]);
    }
    return max_matrix;
}

template<class T>
T system_solver<T>::sum_abs(std::vector<T> vec) {
    T sum = std::fabs(vec[0]);
    for(size_t i = 1; i < vec.size(); i++) {
        sum += std::fabs(vec[i]);
    }
    return sum;
}

// Iter methods
template<class T>
std::pair<matrix<T>, std::vector<T>> system_solver<T>::jacobi_method() {
    matrix<T> alpha(a.size());
    std::vector<T> beta(b.size());
    for (size_t i = 0; i < a.size(); i++) {
        beta[i] = b[i] / a[i][i];
        for (size_t j = 0 ; j < a.size(); j++) {
            if (i == j) {
                alpha[i][j] = 0;
                continue;
            }
            alpha[i][j] = - a[i][j] / a[i][i];
        }
    }
    return std::make_pair(alpha, beta);
}

template<class T>
std::vector<T> system_solver<T>::fixed_point_iterations(size_t &iter) {
    std::vector<std::vector<T>> x;
    std::pair<matrix<T>, std::vector<T>> alpha_beta = jacobi_method();
    x.push_back(alpha_beta.second);
    T eps_k = eps + 1;
    size_t k = 0;
    T norm_alpha = norm_matrix(alpha_beta.first);
    __norm_alpha = norm_alpha;

    if (norm_alpha > 1) {
        std::cout << "error!\n";
        return std::vector<T>();
    }
    while (eps_k >= eps) {
        x.push_back(alpha_beta.second + (alpha_beta.first * x[k]));
        k++;
        eps_k = (norm_alpha / (1 - norm_alpha)) * norm_vec(x[k] - x[k - 1]);
    }
    iter = k;
    return x[k];
}

template<class T>
std::vector<T> system_solver<T>::seidel(size_t &iter) {
    std::vector<std::vector<T>> x;
    std::pair<matrix<T>, std::vector<T>> alpha_beta = jacobi_method();
    x.push_back(alpha_beta.second);
    T eps_k = eps + 1;
    size_t k = 0;
    T norm_alpha = norm_matrix(alpha_beta.first);
    __norm_alpha = norm_alpha;
    T norm_c = norm_matrix(alpha_beta.first);

    while (eps_k >= eps) {
        std::vector<T> xn(a.size(), 0);
        for(int i = 0; i < a.size(); ++i) {
            xn[i] = alpha_beta.second[i];
            for(int j = 0; j < i; ++j) {
                xn[i] += alpha_beta.first[i][j] * xn[j];
            }
            for(int j = i; j < a.size(); ++j) {
                xn[i] += alpha_beta.first[i][j] * x[k][j];
            }
        }
        x.push_back(xn);
        k++;
        eps_k = (norm_c / (1 - norm_alpha)) * norm_vec(x[k] - x[k - 1]);
    }
    iter = k;
    return x[k];
}

template<class T>
bool system_solver<T>::check_solution(std::vector<T> x) {
    T tmp_b = 0; size_t n = a.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            tmp_b += a[i][j] * x[j];
        }
        if (std::fabs(tmp_b - b[i]) > EPS) return false;
        tmp_b = 0;
    }
    return true;
}

template<class T>
void system_solver<T>::check_norm() {
    std::cout << "||Alpha|| = " << __norm_alpha << "\n";
}


#endif //LAB1_3_SYSTEM_SOLVER_HPP
