#ifndef LAB3_1_INTERPOLATION_HPP
#define LAB3_1_INTERPOLATION_HPP

#include "polynomial.hpp"
#include <cmath>

static const double INF = 1e9;

template<class T>
T f(T x) {
    return std::log(x);
}

template<class T>
class interpolation {
public:
    interpolation();
    void push_back(T);
    polynomial_t<T> lagrange_polynomial();
    polynomial_t<T> newton_polynomial();
    T f_dp(size_t, size_t);
    void error(polynomial_t<T>, T);
private:
    size_t n;
    std::vector<T> x;
    std::vector<T> y;
    std::vector<std::vector<T>> divided_differences;

};

template<class T>
interpolation<T>::interpolation(): n(0), x(0), y(0), divided_differences(0) {}

template<class T>
void interpolation<T>::push_back(T num) {
    x.push_back(num);
    y.push_back(f(num));
    n++;
}

template<class T>
void interpolation<T>::error(polynomial_t<T> p_n,T x_err) {
    std::cout << "Погршеность в точке x* = " << x_err << ":\n";
    std::cout << std::fabs(f(x_err) - p_n(x_err)) << "\n";
}

template<class T>
polynomial_t<T> interpolation<T>::lagrange_polynomial() {
    polynomial_t<T> result(n - 1);
    for (size_t i = 0; i < n; i++) {
        polynomial_t<T> l_i(1);
        l_i[0] = 1;
        for (size_t j = 0; j < n; j++) {
            if (i == j) continue;
            polynomial_t<T> tmp(2);
            tmp[0] = -x[j] / (x[i] - x[j]);
            tmp[1] = 1 / (x[i] - x[j]);
            l_i = l_i * tmp;
        }
        result = result + l_i * y[i];
    }
    return result;
}

template<class T>
T interpolation<T>::f_dp(size_t i, size_t j) {
    if (divided_differences[i][j] != INF) {
        return divided_differences[i][j];
    }
    if (i + 1 == j) {
        divided_differences[i][j] = (y[i] - y[j]) / (x[i] - x[j]);
    } else {
        divided_differences[i][j] = (f_dp(i, j - 1) - f_dp(i + 1, j)) / (x[i] - x[j]);
    }
    return divided_differences[i][j];
}

template<class T>
polynomial_t<T> interpolation<T>::newton_polynomial() {
    polynomial_t<T> result(n - 1);
    result[0] = y[0];
    polynomial_t<T> tmp(1);
    tmp[0] = 1;
    divided_differences = std::vector<std::vector<T>>(n, std::vector<T>(n, INF));
    //divided_differences(n, INF);
    for(size_t i = 0; i < n - 1; i++) {
        polynomial_t<T> x_i(2);
        x_i[0] = -x[i];
        x_i[1] = 1;
        tmp = tmp * x_i;

        result = result + (tmp * f_dp(0, i + 1));
    }

    while(result.size() > 0 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}



#endif //LAB3_1_INTERPOLATION_HPP
