#ifndef LAB1_5_QR_HPP
#define LAB1_5_QR_HPP


#include "matrix.hpp"
#include <cmath>
#include <complex>


const static double ZERO = 1e-9;


template<class T>
class qr{
public:
    explicit qr(size_t, T);
    bool check(std::vector<std::complex<T>> &);
    Matrix<T> householder(std::vector<T>);
    int signum (T);
    std::vector<std::complex<T>> qr_decompose();
private:
    Matrix<T> a;
    T eps;
};

template<class T>
qr<T>::qr(size_t n, T epsilon): a(n) {
    a.push_matrix();
    eps = epsilon;
}

template<class T>
int qr<T>::signum(T number) {
    if (number > 0) return 1;
    else if (number == 0) return 0;
    return -1;
}

template<class T>
bool qr<T>::check(std::vector<std::complex<T>> &old_lambda) {
    T sum = 0;
    for(size_t i = 0; i < a.size() - 1; i++) {
        for (size_t j = i + 1; j < a.size(); j++) {
            sum += std::pow(a[i][j], 2);
        }
        if(std::sqrt(sum) <= eps) {
            return false;
        }
        sum = 0;
    }

    std::vector<std::complex<T>> new_lambdas(a.size(), 0);
    for(size_t j = 0; j < a.size(); j++) {
        if(j < a.size() - 1 and std::abs(a[j + 1][j]) > eps) {
            T num_a = 1;
            T num_b = - a[j][j] - a[j + 1][j + 1];
            T num_c = - a[j][j + 1] * a[j + 1][j] + a[j][j] * a[j + 1][j + 1];
            T D = std::pow(num_b, 2) - 4 * num_a * num_c;
            if (D < ZERO) {
                std::complex <T> l1 (- num_b / (2 * num_a), sqrt(- D) / (2 * num_a));
                std::complex <T> l2 (- num_b / (2 * num_a), - sqrt(- D) / (2 * num_a));
                new_lambdas[j] = l1;
                new_lambdas[j + 1] = l2;
                ++j;
            } else {
                new_lambdas[j] = a[j][j];
            }
        } else {
            new_lambdas[j] = a[j][j];
        }
    }

    if(!old_lambda.empty()) {
        for(size_t i = 0; i < old_lambda.size(); ++i) {
            std::complex<T> delta = new_lambdas[i] - old_lambda[i];
            if(std::norm(delta) > eps) {
                old_lambda = new_lambdas;
                return true;
            }
        }
    } else {
        old_lambda = new_lambdas;
        return true;
    }
    return false;
}


template<class T>
Matrix<T> qr<T>::householder(std::vector<T> v) {
    Matrix<T> v1(a.size());
    T v2 = 0;
    Matrix<T> e(a.size());
    e.identity();

    // v * v^T -> matrix
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            v1[i][j] = v[i] * v[j];
        }
    }
    // v^T * v -> number
    for (size_t i = 0; i < a.size(); i++) {
        v2 += v[i] * v[i];
    }

    // (2 * v * v^T) / (v^T * v) -> matrix
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            v1[i][j] = 2 * v1[i][j] / v2;
        }
    }
    // e - (2 * v * v^T) / (v^T * v) -> h - matrix
    Matrix<T> h(a.size());
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a.size(); j++) {
            h[i][j] = e[i][j] - v1[i][j];
        }
    }
    return h;
}


template<class T>
std::vector<std::complex<T>> qr<T>::qr_decompose() {
    std::vector<std::complex<T>> lambda;
    size_t iter = 0;
    Matrix<T> q(a.size());
    Matrix<T> r;
    while (check(lambda)) {
        iter++;
        std::cout << iter << "\n";
        r = a;
        q.identity();
        for (size_t i = 0 ; i < a.size() - 1; i++) {
            std::vector <T> v(a.size(), 0);

            T sum = 0; // euclidean norm
            for (size_t k = i; k < a.size(); k++) {
                sum += std::pow(r[k][i], 2);
            } //
            v[i] = r[i][i] + signum(r[i][i]) * std::sqrt(sum);

            for (size_t j = i + 1; j < a.size(); j++) {
                v[j] = r[j][i];
            }

            Matrix<T> h = householder(v);
            r = h * r;
            q = q * h;
        }
        a = r * q;
    }
    return lambda;
}



#endif //LAB1_5_QR_HPP
