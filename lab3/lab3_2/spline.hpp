#ifndef LAB3_2_SPLINE_HPP
#define LAB3_2_SPLINE_HPP

#include <vector>
#include "numerical.hpp"

template<class T>
class spline_t {
public:
    spline_t(std::vector<T> &, std::vector<T> &, size_t);
    T operator () (T);
private:
    std::vector<T> _x, _y;
    size_t _n;
    std::vector<T> _a, _b, _c, _d;
    void build_spline();
};


template<class T>
T spline_t<T>::operator () (T x) {
    for (size_t i = 1; i < _n; i++) {
        if (_x[i - 1] <= x and x <= _x[i]) {
            double x1 = x - _x[i - 1];
            double x2 = x1 * x1;
            double x3 = x2 * x1;
            return _a[i] + _b[i] * x1 + _c[i] * x2 + _d[i] * x3;
        }
    }
    return NAN;
}


template<class T>
spline_t<T>::spline_t(std::vector<T> &x, std::vector<T> &y, size_t n) :_a(n + 1), _b(n + 1), _c(n + 1), _d(n + 1) {
    this->_x = x;
    this->_y = y;
    _n = n;
    build_spline();
}


template<class T>
void spline_t<T>::build_spline() {
    std::vector<T> h(_n);
    for (size_t i = 1; i < _n; i++) {
        h[i] = _x[i] - _x[i - 1];
    }
    std::vector<T> equation_a(_n - 2);
    std::vector<T> equation_b(_n - 2);
    std::vector<T> equation_c(_n - 2);
    std::vector<T> equation_d(_n - 2);
    for (size_t i = 2; i < _n; i++) {
        equation_a[i - 2] = h[i - 1];
        equation_b[i - 2] = 2.0 * (h[i - 1] + h[i]);
        equation_c[i - 2] = h[i];
        equation_d[i - 2] = 3.0 * ((_y[i] - _y[i - 1]) / h[i] - (_y[i - 1] - _y[i - 2]) / h[i - 1]);
    }
    equation_a[0] = 0.0;
    equation_c.back() = 0.0;
    std::vector<T> solution = numerical::tridiagonal_t<T>::solve(equation_a, equation_b, equation_c, equation_d);

    for (int i = 2; i < _n; i++) {
        _c[i] = solution[i - 2];
        _a[i] = _y[i - 1];
    }
    for (int i = 1; i < _n; i++) {
        _b[i] = (_y[i] - _y[i - 1]) / h[i] - h[i] * (_c[i + 1] + 2.0 * _c[i]) / 3.0;
        _d[i] = (_c[i + 1] - _c[i]) / (3.0 * h[i]);
    }
    _c[1] = 0.0;
    _b.back() = (_y[_n - 1] - _y[_n - 2]) / h[_n - 1] - (2.0 / 3.0) * h[_n - 1] * _c[_n - 1];
    _d.back() = - _c[_n - 1] / (3.0 * h[_n - 1]);
}


#endif //LAB3_2_SPLINE_HPP
