#ifndef LAB3_3_SQUARES_HPP
#define LAB3_3_SQUARES_HPP

#include "numerical.h"

template<class T>
class squares {
public:
    static snm::polynomial_t<T> lsm (std::vector<T> x, std::vector<T> y, size_t p) {
        snm::matrix_t<T> phi(x.size(), p);
        for (size_t i = 0; i < x.size(); i++) {
            for (size_t j = 0; j < p; j++) {
                phi[i][j] = std::pow(x[i], j);
            }
        }
        snm::matrix_t<T> phi_t = phi.transpose();
        snm::matrix_t<T> g = phi_t * phi;
        std::vector<T> z = phi_t * y;


        std::vector<T> dx = snm::lu<T>::solve(g, z);
        return (snm::polynomial_t<T>(dx));
    }
private:
};



#endif //LAB3_3_SQUARES_HPP
