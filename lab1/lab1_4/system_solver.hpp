#ifndef LAB1_4_SYSTEM_SOLVER_HPP
#define LAB1_4_SYSTEM_SOLVER_HPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include "matrix.hpp"

const static double ZERO = 1e-9;

template<class T>
class system_solver{
public:
    explicit system_solver(size_t, T);
    bool t(Matrix<T>);
    std::pair<size_t, size_t> max_elem(Matrix<T>);
    std::vector<T> jacobi_rotation(Matrix<T> &);
private:
    Matrix<T> a;
    T eps;
};


// Implementation
template<class T>
system_solver<T>::system_solver(size_t n, T epsilon): a(n) {
    a.push_matrix();
    eps = epsilon;
}


template<class T>
std::pair<size_t, size_t> system_solver<T>::max_elem(Matrix<T> a_k) {
    T max = std::abs(a_k[0][1]);
    size_t i = 0; size_t j = 1;
    for(size_t m = 0; m < a_k.size(); ++m) {
        for(size_t l = 0; l < a_k.size(); ++l) {
            if(m != l) {
                if(std::abs(a_k[m][l]) > max) {
                    i = m;
                    j = l;
                    max = std::abs(a_k[m][l]);
                }
            }
        }
    }
    return std::make_pair(i, j);
}

template<class T>
bool system_solver<T>::t(Matrix<T> matrix) {
    T sum = 0;
    for(int i = 0; i < matrix.size(); ++i) {
        for(int j = 0; j < matrix.size(); ++j) {
            if(i != j) {
                sum += std::pow(matrix[i][j], 2);
            }
        }
    }
    sum = std::sqrt(sum);
    return sum > eps;
}

template<class T>
std::vector<T> system_solver<T>::jacobi_rotation(Matrix<T> &vecs) {
    std::vector<T> lambda(a.size());
    Matrix<T> a_k = a;
    Matrix<T> u(a.size());
    Matrix<T> u_result(a.size());
    u_result.identity();
    size_t i; size_t j;

    while(t(a_k)) {
        std::pair<size_t, size_t> indexes = max_elem(a_k);
        i = indexes.first; j = indexes.second;
        T phi = M_PI / 4;

        if (std::fabs(a_k[i][i] - a_k[j][j]) > ZERO) { //fabs
            phi = 0.5 * std::atan(2*a_k[i][j] / (a_k[i][i]-a_k[j][j]));
        }

        u.identity();
        u[i][i] = std::cos(phi);
        u[i][j] = - std::sin(phi);
        u[j][i] = std::sin(phi);
        u[j][j] = std::cos(phi);

        Matrix<T> u_transpose = u.transpose();
        a_k = u_transpose * a_k;
        a_k = a_k * u;
        u_result = u_result * u;
    }
    for (size_t k = 0; k < a_k.size(); k++) {
        lambda[k] = a_k[k][k];
    }

    /*for (size_t k = 0; k < a.size(); k++) {
        for (size_t l = 0; l < a.size(); l++) {
            std::cout << u_result[k][l] << " ";
        }
        std::cout << "\n";
    }*/
    vecs = u_result;
    return lambda;
}

#endif //LAB1_4_SYSTEM_SOLVER_HPP