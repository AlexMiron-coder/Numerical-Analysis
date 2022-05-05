#ifndef LAB1_1_LU_HPP
#define LAB1_1_LU_HPP

#include "matrix.hpp"

static const double EPS = 1e-3;

template<class T>
class lu{
public:
    static void lu_decomposition(matrix<T> &, matrix<T> &, matrix<T> &, std::vector<T> &, T &);
    static std::vector<T> lu_solve(matrix<T> &, matrix<T> &, matrix<T> &, std::vector<T> &);
    static matrix<T> invertible(matrix<T> &, matrix<T> &, matrix<T> &, std::vector<T> &);
    static bool check_invertible(matrix<T> &, matrix<T> &);
    static bool check_result(matrix<T>, std::vector<T>, std::vector<T>);
};


template<class T>
void lu<T>::lu_decomposition(matrix<T> &a, matrix<T> &l, matrix<T> &u, std::vector<T> &b, T &det) {
    if (a.isEmpty())
        return;

    u = a;
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = i; j < a.size(); j++) {
            l[j][i] = u[j][i] / u[i][i];
        }
    }
    for (size_t k = 1; k < a.size(); k++) {
        for (size_t i = k - 1; i < a.size(); i++) {
            for (size_t j = i; j < a.size(); j++) {
                l[j][i] = u[j][i] / u[i][i];
            }
        }
        for (size_t i = k; i < a.size(); i++) {
            for (size_t j = k - 1; j < a.size(); j++) {
                u[i][j] = u[i][j] - l[i][k-1] * u[k-1][j];
            }
        }
    }

    for (size_t i = 0; i < a.size(); i++) {
        det *= u[i][i];
    }
}

template<class T>
std::vector<T> lu<T>::lu_solve(matrix<T> &a, matrix<T> &l, matrix<T> &u, std::vector<T> &b) {
    size_t n = a.size();
    std::vector<T> x(n, 0);
    std::vector<T> z(n, 0);
    T sum = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            sum += l[i][j]*z[j];
        }
        z[i] = b[i] - sum;
        sum = 0;
    }
    for (size_t i = n - 1; i >= 0; i--) {
        for (size_t j = i + 1; j < n; j++) {
            sum += u[i][j] * x[j];
        }
        x[i] = (z[i] - sum) / u[i][i];
        sum = 0;
        if (i == 0) break;
    }
    return x;
}

template<class T>
matrix<T> lu<T>::invertible(matrix<T> &a, matrix<T> &l, matrix<T> &u, std::vector<T> &b) {
    size_t n = a.size();
    matrix<T> res(n); std::vector<T> solution(n, 0);
    for (size_t i = 0; i < n; i++) {
        std::vector<T> y(n, 0);
        y[i] = 1;
        std::vector<T> tmp_res = lu_solve(a, l, u, y);
        for (size_t j = 0; j < n; j++) {
            res[j][i] = tmp_res[j];
        }
    }
    return  res;
}

template<class T>
bool lu<T>::check_invertible(matrix<T> &a, matrix<T> &b) {
    size_t n = a.size();
    matrix<T> e; e.identity(n);
    matrix<T> result = a * b;
    for (size_t i = 0; i < n; i++) {
        if (std::abs(result[i][i] - e[i][i]) > EPS) return false;
    }
    return true;
}

template<class T>
bool lu<T>::check_result(matrix<T> a, std::vector<T> x, std::vector<T> b) {
    T tmp_b = 0; size_t n = a.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            tmp_b += a[i][j] * x[j];
        }
        if (std::abs(tmp_b - b[i]) > EPS) return false;
        tmp_b = 0;
    }
    return true;
}


#endif //LAB1_1_LU_HPP
