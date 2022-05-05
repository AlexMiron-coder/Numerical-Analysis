#include <iostream>
#include "iomanip"
#include "lu.hpp"



int main() {
    size_t n; double determinant = 1;
    std::cin >> n;
    matrix<double> a(n); matrix<double> l(n); matrix<double> u(n);
    a.push_matrix();
    std::vector<double> b(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    lu<double>::lu_decomposition(a, l, u, b, determinant);
    //Lu<double> lu(a, l, u, b);
    std::vector<double> result;
    result = lu<double>::lu_solve(a, l, u, b);

    std::cout << "\n\nsolution:\n";
    for (size_t i = 0; i < n; i++) {
        std::cout << std::fixed << std::setprecision(3) << result[i] << " ";
    }
    std::cout << "\n\n";
    std::cout << "determinant = " << std::fixed << std::setprecision(3) << determinant << "\n\n";
    std::cout << "invertible matrix:" << std::endl;
    matrix<double> invertible_matrix = lu<double>::invertible(a, l, u, b);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cout << invertible_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\ncheck A*A^(-1) = E:\n";
    bool check = lu<double>::check_invertible(a, invertible_matrix);
    if (check) std::cout << "OK!\n";
    else std::cout << "ERROR!\n";

    std::cout <<"\ncheck solution: Ax = b\n";
    check = lu<double>::check_result(a, result, b);
    if (check) std::cout << "OK!\n";
    else std::cout << "ERROR!\n";
    return 0;
}

/*
4
3 -8 1 -7
6 4 8 5
-1 1 -9 -3
-6 6 9 -4
96 -13 -54 82

-3 -6 8 -7
 */