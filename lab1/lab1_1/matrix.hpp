#ifndef LAB1_1_MATRIX_HPP
#define LAB1_1_MATRIX_HPP

#include <vector>

template<class T>
class matrix {
public:
    matrix();
    explicit matrix(size_t);
    matrix(size_t, size_t);
    //matrix<T> invertible();
    void identity(size_t);
    void push_matrix();
    bool isEmpty();
    size_t size();
    std::vector<T>& operator [](size_t);
    matrix<T>& operator = (const matrix<T> &);

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
matrix<T>::matrix(size_t n) {
    _n = n; _m = n;
    //_data.resize(n);
    _data = std::vector<std::vector<T>>(n, std::vector<T>(n));
}

template<class T>
matrix<T>::matrix(size_t n, size_t m) {
    _n = n; _m = m;
    //_data.resize(n);
    _data = std::vector<std::vector<T>>(n, std::vector<T>(m, 0));
}

template<class T>
matrix<T>::matrix() {
    _n = 0; _m = 0;
    _data = std::vector<std::vector<T>>();
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
bool matrix<T>::isEmpty() {
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

template<class T>
matrix<T> &matrix<T>::operator=(const matrix<T> &matrix) {
    _n = matrix._n;
    _m = matrix._m;
    _data = matrix._data;
    return *this;
}

template<class T>
void matrix<T>::identity(size_t n) {
    _data = std::vector<std::vector<T>>(n, std::vector<T>(n, 0));
    _n = n; _m = n;
    for (size_t i = 0; i < n; i++) {
        _data[i][i] = 1;
    }
}


#endif //LAB1_1_MATRIX_HPP
