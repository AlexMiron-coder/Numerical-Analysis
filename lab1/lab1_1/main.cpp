#include <iostream>
#include <vector>


class Matrix{
public:
    explicit Matrix(size_t);

    void push(size_t, size_t, int);
    static void luDecomposition(const Matrix& A, Matrix &L, Matrix &U);
    static void solver(const Matrix& A);
    std::vector<int>& operator [](size_t);
private:
    std::vector<std::vector<int>> _data;
};


std::vector<int> &Matrix::operator[](size_t index) {
    return _data[index];
}

Matrix::Matrix(size_t n) {
    _data = std::vector<std::vector<int>>(n, std::vector<int>(n));
}

void Matrix::push(size_t i, size_t j, int num) {
    _data[i][j] = num;
}

void Matrix::luDecomposition(const Matrix& A, Matrix &L, Matrix &U) {
    U = A;
    for (size_t i = 0; i < A._data.size(); i++) {
        for (size_t j = i; j < A._data.size(); j++) {
            L[j][i] = U[j][i] / U[i][i];
        }
    }
    for (size_t k = 1; k < A._data.size(); k++) {
        for (size_t i = k - 1; i < A._data.size(); i++) {
            for (size_t j = i; j < A._data.size(); j++) {
                L[j][i] = U[j][i] / U[i][i];
            }
        }
        for (size_t i = k; i < A._data.size(); i++) {
            for (size_t j = k - 1; j < A._data.size(); j++) {
                U[i][j] = U[i][j] - L[i][k-1] * U[k-1][j];
            }
        }
    }
}

void Matrix::solver(const Matrix& A){
    Matrix L(A._data.size());
    Matrix U(A._data.size());
    luDecomposition(A, L, U);
    std::cout << "L matrix:\n";
    for (size_t i = 0; i < A._data.size(); i++) {
        for (size_t j = 0; j < A._data.size(); j++) {
            std::cout << L[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "U matrix:\n";
    for (size_t i = 0; i < A._data.size(); i++) {
        for (size_t j = 0; j < A._data.size(); j++) {
            std::cout << U[i][j] << " ";
        }
        std::cout << "\n";
    }
}


int main() {
    size_t n;
    int num;
    std::cin >> n;
    Matrix A(n);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cin >> num;
            A.push(i, j, num);
        }
    }
    Matrix::solver(A);
    return 0;
}
