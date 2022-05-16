#include <iostream>
#include <iomanip>
#include "function.hpp"

int main() {
    std::pair<double, double> x_y;
    size_t iteration = 0;

    x_y = function<double>::newtons_method(0.2, 0.8, iteration);
    std::cout << "Newton's method:\n";
    std::cout << std::fixed << std::setprecision(2) << x_y.first << " " << x_y.second <<
    "\niterations = " << iteration << "\n";
    iteration = 0;

    x_y = function<double>::fixed_point_iteration(0.1, 1.5, 1.5, 2.3, iteration);
    std::cout << "Fixed-point iterations method:\n";
    std::cout << std::fixed << std::setprecision(2) << x_y.first << " " << x_y.second <<
              "\niterations = " << iteration << "\n";
    return 0;
}
