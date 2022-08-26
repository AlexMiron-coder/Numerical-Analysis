#include <iostream>
#include "integral.hpp"


int main() {
    double r = 0.001;
    double x0, xk;
    double h1, h2;
    std::cin >> x0 >> xk >> h1 >> h2;

    double rec1 = integral_t<double>::rectangle_method(x0, xk, h1), rec2 = integral_t<double>::rectangle_method(x0, xk, h2);
    double trap1 = integral_t<double>::trapezoid_method(x0, xk, h1), trap2 = integral_t<double>::trapezoid_method(x0, xk, h2);
    double sim1 = integral_t<double>::simpson_method(x0, xk, h1), sim2 = integral_t<double>::simpson_method(x0, xk, h2);

    std::cout << "Шаг h = " << h1 << std::endl;
    std::cout << "Метод прямоугольников: " << rec1 << std::endl;
    std::cout << "Метод трапеций: " << trap1 << std::endl;
    std::cout << "Метод Симпсона: " << sim1 << "\n\n";

    std::cout << "Шаг h = " << h2 << std::endl;
    std::cout << "Метод прямоугольников: " << rec2 << std::endl;
    std::cout << "Метод трапеций: " << trap2 << std::endl;
    std::cout << "Метод Симпсона: " << sim2 << "\n\n";

    std::cout << "Погрешность вычислений методом Рунге-Ромберга:" << std::endl;
    std::cout << "Метод прямоугольников: " << integral_t<double>::runge_romberg_method(rec1, rec2, h2 / h1, 1) << std::endl;
    std::cout << "Метод трапеций: " << integral_t<double>::runge_romberg_method(trap1, trap2, h2 / h1, 2) << std::endl;
    std::cout << "Метод Симпсона: " << integral_t<double>::runge_romberg_method(sim1, sim2, h2 / h1, 4) << std::endl;
}

/*
-1 1 0.5 0.25

 */