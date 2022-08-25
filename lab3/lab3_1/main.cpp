#include <iostream>
#include "interpolation.hpp"

int main() {
    double x, x_err; size_t n;
    interpolation<double> interpolator;

    std::cin >> n;
    for (size_t i = 0; i < n; i++) {
        std::cin >> x;
        interpolator.push_back(x);
    }
    std::cin >> x_err;

    polynomial_t<double> result_lagrange = interpolator.lagrange_polynomial();
    std::cout << "Lagrange polynomial:\n";
    for (size_t i = 0; i < result_lagrange.size(); i++) {
        std::cout << result_lagrange[i] << " ";
    }
    std::cout << "\n";
    std::cout << result_lagrange;
    std::cout << "\n\n";

    polynomial_t<double> result_newton = interpolator.newton_polynomial();
    std::cout << "Newton polynomial:\n";
    for (size_t i = 0; i < result_lagrange.size(); i++) {
        std::cout << result_newton[i] << " ";
    }
    std::cout << "\n";
    std::cout << result_newton;
    std::cout << "\n\n";

    interpolator.error(result_lagrange, x_err);
    interpolator.error(result_newton, x_err);
    return 0;
}

/*
4
0.2 0.6 1.0 1.4
0.8
 */