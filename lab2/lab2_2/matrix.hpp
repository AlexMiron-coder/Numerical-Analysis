#ifndef LAB2_2_MATRIX_HPP
#define LAB2_2_MATRIX_HPP

#include <iostream>
#include <vector>
#include "math.h"


template<class T>
std::vector<T> operator + (const std::vector<T> &lhs, const std::vector<T> &rhs) {
    std::vector<T> result(lhs.size());
    for (size_t i = 0; i < lhs.size(); i++) {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

template<class T>
std::vector<T> operator - (const std::vector<T> &lhs, const std::vector<T> &rhs) {
    std::vector<T> result(lhs.size());
    for (size_t i = 0; i < lhs.size(); i++) {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}


template<class T>
T norm(std::vector<T> vec) {
    T max = std::abs(vec[0]);
    for (auto &v : vec) {
        if (std::abs(v) > max) max = std::abs(v);
    }
    return max;
}



template<class T>
class matrix{
public:
    matrix();
    explicit matrix(size_t);
    matrix(size_t, size_t);
    void identity();
    matrix<T> transpose();
    void push_matrix();
    bool is_empty();
    size_t size();
    std::vector<T>& operator [](size_t);
    //Matrix<T>& operator = (const Matrix<T> &);

    friend std::vector<T> operator * (matrix<T> &mat, std::vector<T> &vec) {
        std::vector<T> result(vec.size(), 0);
        T res = 0;
        for (size_t i = 0; i < vec.size(); i++) {
            for (size_t j = 0; j < vec.size(); j++) {
                result[i] += mat[i][j] * vec[j];
            }
        }
        return result;
    }
    friend matrix<T> operator * (matrix<T> &a, matrix<T> &b) {
        size_t n = a.size();
        matrix<T> result(n);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                for (size_t k = 0; k < n; ++k) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return result;
    }
private:
    size_t _n;
    size_t _m;
    std::vector<std::vector<T>> _data;
};


// Implementation
template<class T>
matrix<T>::matrix() {
    _n = 0, _m = 0;
    _data = std::vector<std::vector<T>>();
}

template<class T>
matrix<T>::matrix(size_t n) {
    _n = n, _m = n;
    _data = std::vector<std::vector<T>>(n, std::vector<T>(n, 0));
}

template<class T>
matrix<T>::matrix(size_t n, size_t m) {
    _n = n, _m = m;
    _data = std::vector<std::vector<T>>(n, std::vector<T>(m));
}

template<class T>
void matrix<T>::identity() {
    _data = std::vector<std::vector<T>>(_n, std::vector<T>(_m, 0));
    for (size_t i = 0; i < _n; i++) {
        _data[i][i] = 1;
    }
}

template<class T>
matrix<T> matrix<T>::transpose() {
    matrix<T> transposed_m(_n);
    for(int i = 0; i < _n; i++) {
        for (int j = 0; j < _m; j++) {
            transposed_m[j][i] = _data[i][j];
        }
    }
    return transposed_m;
}


template<class T>
std::vector<T> &matrix<T>::operator[](size_t index) {
    return _data[index];
}

template<class T>
size_t matrix<T>::size() {
    return _n;
}

template<class T>
bool matrix<T>::is_empty() {
    if (_data.empty())
        return true;
    return false;
}

template<class T>
void matrix<T>::push_matrix() {
    for (size_t i = 0; i < _n; i++) {
        for (size_t j = 0; j < _m; j++) {
            std::cin >> _data[i][j];
        }
    }
}

/*
template<class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix) {
    _n = matrix._n;
    _m = matrix._m;
    _data = matrix._data;
    return *this;
}*/


#endif //LAB2_2_MATRIX_HPP
