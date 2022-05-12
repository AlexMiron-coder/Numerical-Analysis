#ifndef LAB2_2_FUNCTION_HPP
#define LAB2_2_FUNCTION_HPP

const static int a = 2;

double EPS = 0.001;

#include "matrix.hpp"
#include "lu.hpp"
#include "math.h"

template<class T>
class function {
public:
    std::pair<T, T> newtons_method(T, T, size_t &);
private:
    static T f1(T, T);
    static T f2(T, T);
};

// Implementation

template<class T>
T function<T>::f1(T x1, T x2) {
    return x1 - std::cos(x2) - 1;
}

template<class T>
T function<T>::f2(T x1, T x2) {
    return x2 - std::log10(x1 + 1) - a;
}

template<class T>
std::pair<T, T> function<T>::newtons_method(T x1_0, T x2_0, size_t &iter) {
    T eps_k;
    std::vector<T> x_k = {x1_0, x2_0};
    do {
        iter++;

    } while (eps_k > EPS);
}


#endif //LAB2_2_FUNCTION_HPP
