#include <iostream>
#include "squares.hpp"


int main() {
    size_t n;
    std::cin >> n;
    std::vector<double> x(n), y(n);

    for (size_t i = 0; i < n; i++) std::cin >> x[i];
    for (size_t i = 0; i < n; i++) std::cin >> y[i];

    std::cout << "Приближающий многочлен 1-ой степени" << std::endl;
    snm::polynomial_t<double> polynomial1 = squares<double>::lsm(x, y, 2);
    std::cout << polynomial1 << std::endl;

    std::cout << squares<double>::square_error(x ,y, polynomial1) << std::endl;

    std::cout << "Приближающий многочлен 2-ой степени" << std::endl;
    snm::polynomial_t<double> polynomial2 = squares<double>::lsm(x, y, 3);
    std::cout << polynomial2 << std::endl;
    std::cout << squares<double>::square_error(x ,y, polynomial2) << std::endl;
    return 0;
}

/*
6
0.1 0.5 0.9 1.3 1.7 2.1
-2.3026 -0.69315 -0.10536 0.26236 0.53063 0.74194

 */