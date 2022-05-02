#include "system_solver.hpp"

int main() {
    size_t n; double eps;
    std::cin >> n >> eps;
    system_solver<double> system(n, eps);
    Matrix<double> vecs(n);
    std::vector<double> result = system.jacobi_rotation(vecs);

    std::cout << "precision = " << eps << "\n\n";
    std::cout << "eigenvalues:\n";
    for (double i : result) {
        std::cout << std::fixed << std::setprecision(3) << i << " ";
    }

    std::cout << "\n\neigenvectors:\n";
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cout << std::fixed << std::setprecision(3) << vecs[i][j] << " ";
        }
        std::cout << "\n";
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