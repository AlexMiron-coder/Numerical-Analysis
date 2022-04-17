#include <iostream>
#include "lu.hpp"



int main() {
    size_t n;
    std::cin >> n;
    Lu<double> lu(n);
    std::vector<double> result;
    result = lu.solve();
    for (size_t i = 0; i < n; i++) {
        std::cout << result[i] << " ";
    }
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