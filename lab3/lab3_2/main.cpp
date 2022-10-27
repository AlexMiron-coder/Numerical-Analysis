#include <iostream>
#include "spline.hpp"

int main() {
    double x0; size_t n;
    std::cin >> x0 >> n;
    std::vector<double> x(n);
    std::vector<double> y(n);
    for (size_t i = 0; i < n; i++) std::cin >> x[i];
    for (size_t i = 0; i < n; i++) std::cin >> y[i];
    spline_t<double> spline(x, y, n);

    std::cout << spline(x0) << std::endl;
    return 0;
}


/*
0.8
5
0.1 0.5 0.9 1.3 1.7
-2.3026 -0.69315 -0.10536 0.26236 0.53063

 */