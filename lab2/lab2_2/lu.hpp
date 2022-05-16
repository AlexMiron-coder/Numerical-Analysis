#ifndef LAB2_2_LU_HPP
#define LAB2_2_LU_HPP

#include "matrix.hpp"



static const double EPS = 1e-3;


template<class T>
class lu {
public:
    static std::vector<T> solve(matrix<T>, std::vector<T>);
private:
    static void lu_decomposition(matrix<T> &, matrix<T> &, matrix<T> &);

    //static matrix<T> invertible(matrix<T> &, matrix<T> &, matrix<T> &, std::vector<T> &);
    //static bool check_invertible(matrix<T> &, matrix<T> &);
};


template<class T>
void lu<T>::lu_decomposition(matrix<T> &a, matrix<T> &l, matrix<T> &u) {
    if (a.is_empty())
        return;

    u = a; l = a;
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
                u[i][j] = u[i][j] - l[i][k - 1] * u[k - 1][j];
            }
        }
    }
}

template<class T>
std::vector<T> lu<T>::solve(matrix<T> a, std::vector<T> b) {
    matrix<T> l, u;
    lu_decomposition(a, l, u);
    size_t n = a.size();
    std::vector<T> x(n, 0);
    std::vector<T> z(n, 0);
    T sum = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            sum += l[i][j] * z[j];
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


#endif //LAB2_2_LU_HPP
