#ifndef LAB3_5_INTEGRAL_HPP
#define LAB3_5_INTEGRAL_HPP


#include "math.h"

template<class T>
class integral_t {
public:
    static T rectangle_method(T, T, T);
    static T trapezoid_method(T, T, T);
    static T simpson_method(T, T, T);
    static T runge_romberg_method(T, T, T, int);
private:
    static T f (T);
};



template<class T>
T integral_t<T>::f (T x) {
    return 1 / ((2*x + 7)*(3*x + 4));
}

template<class T>
T integral_t<T>::rectangle_method(T x_0, T x_k, T h) {
    T xi_0 = x_0;
    T xi_1 = x_0 + h;
    T result = 0;

    do {
        result += h * f((xi_0 + xi_1) / 2);
        xi_0 += h;
        xi_1 += h;
    } while (xi_0 < x_k);
    return result;
}

template<class T>
T integral_t<T>::trapezoid_method(T x_0, T x_k, T h) {
    T xi_0 = x_0;
    T xi_1 = x_0 + h;
    T result = 0;
    do {
        result += h * (f(xi_1) + f(xi_0));
        xi_0 += h;
        xi_1 += h;
    } while (xi_0 < x_k);
    return result / 2;
}

template<class T>
T integral_t<T>::simpson_method(T x_0, T x_k, T h) {
    double xi_0;
    double res = f(x_0) + f(x_k);

    xi_0 = x_0 + h / 2;
    do {
        res += 4 * f(xi_0 / 2);
        xi_0 += h;
    } while (xi_0 < x_k);

    xi_0 = x_0 + h;
    do {
        res += 2 * f(xi_0);
        xi_0 += h;
    } while (xi_0 < x_k);

    return res * h / 3;
}

template<class T>
T integral_t<T>::runge_romberg_method(T Ir,T I, T r, int p) {
    return std::abs((Ir - I) / (pow(r, p) - 1));

}


#endif //LAB3_5_INTEGRAL_HPP
