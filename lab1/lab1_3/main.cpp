#include <iomanip>
#include "system_solver.hpp"

int main() {
    size_t n; double eps;
    std::cin >> n >> eps;
    system_solver<double> system(n, eps);
    std::vector<double> res = system.fixed_point_iterations();
    for (double re : res) {
        std::cout << std::fixed << std::setprecision(3) << re << " ";
    }
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