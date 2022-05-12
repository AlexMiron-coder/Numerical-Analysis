#include "function.hpp"
#include <iomanip>

int main() {
    double precision; size_t iterations = 0;
    double left; double right;
    std::cin >> precision;
    EPS = precision;
    while (std::cin >> left >> right) {
        double x = function<double>::fixed_point_iteration(left, right, iterations);
        std::cout << "fixed-point iteration method:\n";
        std::cout << std::fixed << std::setprecision(3) << "x = " << x
                  << "\nnum of iterations: " << iterations << "\n\n";
        iterations = 0;

        x = function<double>::newtons_method(right, iterations);
        std::cout << "Newton's method:\n";
        std::cout << std::fixed << std::setprecision(3) << "x = " << x
                  << "\nnum of iterations: " << iterations << "\n\n";
        iterations = 0;
    }
    return 0;
}

/*
0.001
1 2
4 5

result:
1.427 6
4.146 3

*/