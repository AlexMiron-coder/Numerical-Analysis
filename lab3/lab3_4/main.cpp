#include "differentiation.hpp"

int main() {
    size_t n; double x0;
    std::cin >> n >> x0;
    std::vector<double> x(n), y(n);
    for (size_t i = 0; i < n; i++) std::cin >> x[i];
    for (size_t i = 0; i < n; i++) std::cin >> y[i];

    std::cout << "Первая производная таблично заданной функции:\n";
    std::cout << derivative<double>::diff_first(x, y, x0) << std::endl;
    std::cout << "Вторая производная таблично заданной функции:\n";
    std::cout << derivative<double>::diff_second(x, y, x0) << std::endl;
    return 0;
}
/*
5 2
0 1 2 3 4
0 1 1.4142 1.7321 2
 */