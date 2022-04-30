#include <iostream>
#include "tridiagonal_matrix.hpp"

int main() {
    size_t n;
    std::cin >> n;
    TridiagonalMatrix<double> system(n);
    std::vector<double> result = system.solve();
    for (double i : result) {
        std::cout << i << " ";
    }
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


4
8 -2
-1 6 -2
2 10 -4
-1 6
6 3 8 5
 */
