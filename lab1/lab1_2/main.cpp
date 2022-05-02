#include <iostream>
#include <iomanip>
#include "tridiagonal_matrix.hpp"

int main() {
    size_t n;
    std::cin >> n;
    TridiagonalMatrix<double> system(n);
    std::vector<double> result = system.solve();
    for (double i : result) {
        std::cout << std::fixed << std::setprecision(3) << i << " ";
    }
    std::cout << "\n";
    if (system.checkResult(result)) std::cout << "OK!\n";
    else std::cout << "ERROR!\n";
    return 0;
}

/*
5
8 4
-5 22 8
-5 -11 1
-9 -15 1
1 7
48 125 -43 18 -23
 */
