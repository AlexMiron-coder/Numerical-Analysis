#include <iomanip>
#include "system_solver.hpp"

int main() {
    size_t n; double eps; bool check;
    std::cin >> n >> eps;
    system_solver<double> system(n, eps);
    size_t k1; size_t k2;

    std::cout << "Precision: " << eps << "\n\n";

    std::cout << "Fixed-point iteration method:\n";
    std::vector<double> res1 = system.fixed_point_iterations(k1);
    std::cout << "num of iterations: " << k1 << "\n";
    system.check_norm();
    std::cout << "solution:\n";
    for (double re : res1) {
        std::cout << std::fixed << std::setprecision(3) << re << " ";
    }
    std::cout << "\n\n";

    std::cout << "Seidel method:\n";
    std::vector<double> res2 = system.seidel(k2);
    std::cout << "num of iterations: " << k2 << "\n";
    system.check_norm();
    std::cout << "solution:\n";
    for (double re : res2) {
        std::cout << std::fixed << std::setprecision(3) << re << " ";
    }
    std::cout << "\n\n";

    std::cout << "check solution:\n";
    check = system.check_solution(res1);
    if (check) std::cout << "OK!\n";
    else std::cout << "ERROR!\n";
    return 0;
}
/*
4
0.001
20 5 7 1
-1 13 0 -7
4 -6 17 5
-9 8 4 -25
-117 -1 49 -21

ans: -8 2 4 5
 */