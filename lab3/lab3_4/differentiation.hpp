#ifndef LAB3_4_DIFFERENTIATION_HPP
#define LAB3_4_DIFFERENTIATION_HPP

#include <iostream>
#include <vector>


template<class T>
class derivative {
public:
    static T diff_first(std::vector<T>, std::vector<T>, T);
    static T diff_second(std::vector<T>, std::vector<T>, T);
private:
};

template<class T>
T derivative<T>::diff_first(std::vector<T> x, std::vector<T> y, T x0) {
    size_t id = 0;
    for (size_t i = 0; i < x.size() - 2; i++) {
        if (x0 >= x[i] and x0 <= x[i + 1]) {
            id = i;
            break;
        }
    }
    T res = (y[id + 1] - y[id + 0]) / (x[id + 1] - x[id + 0])
            + ((y[id + 2] - y[id + 1]) / (x[id + 2] - x[id + 1])
            - (y[id + 1] - y[id + 0]) / (x[id + 1] - x[id + 0]))
            * (2.0 * x0 - x[id] - x[id + 1]) / (x[id + 2] - x[id]);
    return res;
}

template<class T>
T derivative<T>::diff_second(std::vector<T> x, std::vector<T> y, T x0) {
    size_t id = 0;
    for (size_t i = 0; i < x.size() - 2; i++) {
        if (x0 >= x[i] and x0 <= x[i + 1]) {
            id = i;
            break;
        }
    }
    T res = 2.0 * ((y[id + 2] - y[id + 1]) / (x[id + 2] - x[id + 1])
                   - (y[id + 1] - y[id + 0]) / (x[id + 1] - x[id + 0]))
                           / (x[id + 2] - x[id]);
    return res;
}

#endif //LAB3_4_DIFFERENTIATION_HPP
