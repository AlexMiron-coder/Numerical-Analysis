#ifndef LAB1_2_TRIDIAGONAL_MATRIX_HPP
#define LAB1_2_TRIDIAGONAL_MATRIX_HPP

#include <vector>

template<class T>
class TridiagonalMatrix{
public:
    TridiagonalMatrix(size_t);
    void getSystem();
    std::vector<T> solve();
private:
    size_t n;
    std::vector<T> _a;
    std::vector<T> _b;
    std::vector<T> _c;
    std::vector<T> _d;
};


// Implementation
template<class T>
TridiagonalMatrix<T>::TridiagonalMatrix<class T>(size_t size) : _a(size), _b(size), _c(size), _d(size) {
    n = size;
    getSystem();
}

template<class T>
int TridiagonalMatrix<T>::getSystem() {
    std::cin >> _b[0] >> _c[0]; // a[0] = 0
    for (size_t i = 1; i < n - 1; i++) {
        std::cin >> _a[i] >> _b[i] >> _c[i];
    }
    std::cin >> _a[n - 1] >> _b[n - 1]; // c[n - 1] = 0

    for (size_t i = 0; i < n; i++) {
        std::cin >> _d[i];
    }
}

template<class T>
std::vector<T> TridiagonalMatrix<T>::solve() {
    std::vector<T> x(n, 0);
    return x;
}


#endif //LAB1_2_TRIDIAGONAL_MATRIX_HPP
