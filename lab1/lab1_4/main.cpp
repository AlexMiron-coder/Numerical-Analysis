#include "system_solver.hpp"

int main() {
    size_t n; double eps;
    std::cin >> n >> eps;
    system_solver<double> system(n, eps);
    std::vector<double> result = system.jacobi_rotation();
    for (double i : result) {
        std::cout << i << " ";
    }
    return 0;
}
/*
3
0.001
0 -7 7
-7 -9 -5
7 -5 -1
 */