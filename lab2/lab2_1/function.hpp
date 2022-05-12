#ifndef LAB2_1_FUNCTION_HPP
#define LAB2_1_FUNCTION_HPP

#include <iostream>
#include <math.h>
#include <vector>

static double EPS = 0.01;

template<class T>
class function {
public:
    static T fixed_point_iteration(T, T, size_t &);
    static T newtons_method(T, size_t &);
private:
    static T f(T);
    static T df(T);
    static T phi(T);
    static T dphi(T);
    static T sign(T);
};


// Implementation

template<class T>
T function<T>::f(T x) {
    return std::cos(x) + 0.25*x - 0.5;
}

template<class T>
T function<T>::df(T x) {
    return - std::sin(x) + 0.25;
}

template<class T>
T function<T>::phi(T x) {
    return (0.5 - std::cos(x)) / 0.25;
}

template<class T>
T function<T>::dphi(T x) {
    return std::sin(x) / 0.25;
}

template<class T>
T function<T>::sign(T x) {
    return x > 0 ? 1: x < 0 ? -1 : 0;
}

template<class T>
T function<T>::fixed_point_iteration(T a, T b, size_t &iterations) {
    T x_k = a; T x_k1;
    T eps_k;
    T lambda = sign(df(x_k) / std::max(std::abs(a), std::abs(b)));
    T q = std::max(std::abs(1 - lambda * df(a)), std::abs(1 - lambda * df(b)));
    q = q / (1 - q);
    do {
        x_k1 = x_k - lambda * f(x_k);
        iterations++;
        eps_k = q * std::abs(x_k - x_k1);
        x_k = x_k1;
    } while (eps_k > EPS);
    return x_k;
}

template<class T>
T function<T>::newtons_method(T x0, size_t &iterations) {
    T x_k = x0; T x_k1;
    T eps_k;
    do {
        x_k1 = x_k - f(x_k) / df(x_k);
        iterations++;
        eps_k = std::abs(x_k1 - x_k);
        x_k = x_k1;
    } while (eps_k > EPS);
    return x_k;
}

#endif //LAB2_1_FUNCTION_HPP
