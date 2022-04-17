#ifndef LAB1_1_LU_HPP
#define LAB1_1_LU_HPP

#include "matrix.hpp"

template<class T>
class Lu{
public:
    explicit Lu(size_t);
    void getB();
    void luDecomposition();
    std::vector<T> solve();
private:
    Matrix<T> _a;
    std::vector<T> _b;
    Matrix<T> _l;
    Matrix<T> _u;
};


// Implementation
template<class T>
Lu<T>::Lu(size_t size) : _a(size), _b(size), _l(size), _u(size) {
    //_a = Matrix<T>(size);
    _a.push_matrix();
    getB();
    luDecomposition();
}

template<class T>
void Lu<T>::getB() {
    for (size_t i = 0; i < _a.size(); i++) {
        std::cin >> _b[i];
    }
}

template<class T>
void Lu<T>::luDecomposition() {
    if (_a.isEmpty())
        return;

    _u = _a;
    for (size_t i = 0; i < _a.size(); i++) {
        for (size_t j = i; j < _a.size(); j++) {
            _l[j][i] = _u[j][i] / _u[i][i];
        }
    }
    for (size_t k = 1; k < _a.size(); k++) {
        for (size_t i = k - 1; i < _a.size(); i++) {
            for (size_t j = i; j < _a.size(); j++) {
                _l[j][i] = _u[j][i] / _u[i][i];
            }
        }
        for (size_t i = k; i < _a.size(); i++) {
            for (size_t j = k - 1; j < _a.size(); j++) {
                _u[i][j] = _u[i][j] - _l[i][k-1] * _u[k-1][j];
            }
        }
    }
}

template<class T>
std::vector<T> Lu<T>::solve() {
    size_t n = _a.size();
    std::vector<T> x(n, 0);
    std::vector<T> z(n, 0);
    T sum = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            sum += _l[i][j]*z[j];
        }
        z[i] = _b[i] - sum;
        sum = 0;
    }
    for (size_t i = n - 1; i >= 0; i--) {
        for (size_t j = i + 1; j < n; j++) {
            sum += _u[i][j] * x[j];
        }
        x[i] = (z[i] - sum) / _u[i][i];
        sum = 0;
        if (i == 0) break;
    }
    return x;
}




#endif //LAB1_1_LU_HPP
