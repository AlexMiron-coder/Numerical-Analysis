#ifndef LAB1_4_MATRIX_HPP
#define LAB1_4_MATRIX_HPP

#include <vector>


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
class Matrix{
public:
    Matrix();
    explicit Matrix(size_t);
    Matrix(size_t, size_t);
    void identity();
    Matrix<T> transpose();
    void push_matrix();
    bool isEmpty();
    size_t size();
    std::vector<T>& operator [](size_t);
    //Matrix<T>& operator = (const Matrix<T> &);

    friend std::vector<T> operator * (Matrix<T> &mat, std::vector<T> &vec) {
        std::vector<T> result(vec.size(), 0);
        T res = 0;
        for (size_t i = 0; i < vec.size(); i++) {
            for (size_t j = 0; j < vec.size(); j++) {
                result[i] += mat[i][j] * vec[j];
            }
        }
        return result;
    }
    friend Matrix<T> operator * (Matrix<T> &a, Matrix<T> &b) {
        size_t n = a.size();
        Matrix<T> result(n);
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
Matrix<T>::Matrix() {
    _n = 0, _m = 0;
    _data = std::vector<std::vector<T>>();
}

template<class T>
Matrix<T>::Matrix(size_t n) {
    _n = n, _m = n;
    _data = std::vector<std::vector<T>>(n, std::vector<T>(n, 0));
}

template<class T>
Matrix<T>::Matrix(size_t n, size_t m) {
    _n = n, _m = m;
    _data = std::vector<std::vector<T>>(n, std::vector<T>(m));
}

template<class T>
void Matrix<T>::identity() {
    _data = std::vector<std::vector<T>>(_n, std::vector<T>(_m, 0));
    for (size_t i = 0; i < _n; i++) {
        _data[i][i] = 1;
    }
}

template<class T>
Matrix<T> Matrix<T>::transpose() {
    Matrix<T> transposed_m(_n);
    for(int i = 0; i < _n; i++) {
        for (int j = 0; j < _m; j++) {
            transposed_m[j][i] = _data[i][j];
        }
    }
    return transposed_m;
}


template<class T>
std::vector<T> &Matrix<T>::operator[](size_t index) {
    return _data[index];
}

template<class T>
size_t Matrix<T>::size() {
    return _n;
}

template<class T>
bool Matrix<T>::isEmpty() {
    if (_data.empty())
        return true;
    return false;
}

template<class T>
void Matrix<T>::push_matrix() {
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


#endif //LAB1_4_MATRIX_HPP
