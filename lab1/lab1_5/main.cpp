#include <iomanip>
#include "qr.hpp"


int main() {
    size_t n; double eps;
    std::cin >> n >> eps;
    qr<double> qr(n, eps);
    std::vector<std::complex<double>> res = qr.qr_decompose();
    for (auto & re : res) {
        std::cout << std::fixed << std::setprecision(5) << re << " ";
    }
    return 0;
}
/*
3
0.001
5 8 -2
7 -2 -4
5 8 -1
 */