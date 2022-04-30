#ifndef LAB1_2_TRIDIAGONAL_MATRIX_HPP
#define LAB1_2_TRIDIAGONAL_MATRIX_HPP

#include <vector>

static const double EPS = 0.01;


template<class T>
class TridiagonalMatrix{
public:
    explicit TridiagonalMatrix(size_t);
    void getSystem();
    bool checkResult(std::vector<T> &);
    std::vector<T> solve();
private:
    size_t n;
    std::vector<T> a;
    std::vector<T> b;
    std::vector<T> c;
    std::vector<T> d;
};


// Implementation
template<class T>
TridiagonalMatrix<T>::TridiagonalMatrix(size_t size) : a(size, 0), b(size, 0), c(size, 0), d(size, 0) {
    n = size;
    getSystem();
}

template<class T>
void TridiagonalMatrix<T>::getSystem() {
    std::cin >> b[0] >> c[0]; // a[0] = 0
    for (size_t i = 1; i < n - 1; i++) {
        std::cin >> a[i] >> b[i] >> c[i];
    }
    std::cin >> a[n - 1] >> b[n - 1]; // c[n - 1] = 0

    for (size_t i = 0; i < n; i++) {
        std::cin >> d[i];
    }
}

template<class T>
std::vector<T> TridiagonalMatrix<T>::solve() {
    std::vector<T> x(n);
    std::vector<T> p(n);
    std::vector<T> q(n);
    p[0] = -c[0] / b[0];
    q[0] = d[0] / b[0];
    for (size_t i = 1; i < n - 1; i++) {
        p[i] = -c[i] / (b[i] + a[i] * p[i-1]);
        q[i] = (d[i] - a[i] * q[i-1]) / (b[i] + a[i] * p[i-1]);
    }
    p[n - 1] = 0;
    q[n - 1] = (d[n-1] - a[n-1]*q[n-2]) / (b[n-1] - a[n-1]*p[n-2]);

    x[n - 1] = q[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = p[i]*x[i + 1] + q[i];
    }
    return x;
}

template<class T>
bool TridiagonalMatrix<T>::checkResult(std::vector<T> &x) {
    if (abs(b[0]*x[0] + c[0]*x[1] - d[0]) > EPS) return false;
    for (size_t i = 1; i < n - 1; i++) {
        if (abs(a[i]*x[i - 1] + b[i]*x[i] + c[i]*x[i + 1] - d[i]) > EPS) return false;
    }
    if (abs(a[n - 1]*x[n - 2] + b[n - 1]*x[n - 1] - d[n - 1]) > EPS) return false;
    return true;
}



#endif //LAB1_2_TRIDIAGONAL_MATRIX_HPP
