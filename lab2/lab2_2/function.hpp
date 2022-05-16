#ifndef LAB2_2_FUNCTION_HPP
#define LAB2_2_FUNCTION_HPP


#include "matrix.hpp"
#include "lu.hpp"

template<class T>
class function {
public:
    static std::pair<T, T> newtons_method(T, T, size_t &);
    static std::pair<T, T> fixed_point_iteration(T, T, T, T, size_t &);
private:
    static matrix<T> jacobi_matrix(T, T);
    static T f1(T, T);
    static T f2(T, T);
    static T phi1(T);
    static T phi2(T);
    static T dphi1(T);
    static T dphi2(T);
};

// Implementation

template<class T>
T function<T>::f1(T x1, T x2) {
    return x1 - std::cos(x2) - 1;
}

template<class T>
T function<T>::f2(T x1, T x2) {
    return x2 - std::log10(x1 + 1) - 2;
}

template<class T>
T function<T>::phi1(T x2) {
    return 1 + std::cos(x2);
}

template<class T>
T function<T>::phi2(T x1) {
    return 2 + std::log10(x1 + 1);
}

template<class T>
T function<T>::dphi1(T x2) {
    return -std::sin(x2);
}

template<class T>
T function<T>::dphi2(T x1) {
    return 1 / ((x1 + 1)*std::log(10));
}

template<class T>
matrix<T> function<T>::jacobi_matrix(T x1, T x2) {
    matrix<T> j(2);
    j.identity();
    j[0][1] = std::sin(x2);
    j[1][0] = -1 / (x1 + 1)*std::log(10);
    return j;
}


template<class T>
std::pair<T, T> function<T>::newtons_method(T x1_0, T x2_0, size_t &iter) {
    T eps_k; matrix<T> j;
    std::vector<T> f_k, dx, x_k1;
    std::vector<T> x_k = {x1_0, x2_0};
    do {
        iter++;
        j = jacobi_matrix(x_k[0], x_k[1]);
        f_k = {-f1(x_k[0], x_k[1]), -f2(x_k[0], x_k[1])};
        dx = lu<T>::solve(j, f_k);
        x_k1 = x_k + dx;
        eps_k = norm(x_k1 - x_k);
        x_k = x_k1;
    } while (eps_k > EPS);
    return std::make_pair(x_k[0], x_k[1]);
}

template<class T>
std::pair<T, T> function<T>::fixed_point_iteration(T a1, T b1, T a2, T b2, size_t &iter) {
    T q = -1e3; T eps_k;
    std::vector<T> x_k = {b1, b2};
    std::vector<T> x_k1(2);
    q = std::max(q, std::abs(dphi1(b1)* dphi2(a1)));
    q = std::max(q, std::abs(dphi1(b2)* dphi2(a1)));
    q = std::max(q, std::abs(dphi1(b1)* dphi2(a2)));
    q = std::max(q, std::abs(dphi1(b2)* dphi2(a2)));
    do {
        iter++;
        x_k1[0] = phi1(x_k[1]);
        x_k1[1] = phi2(x_k[0]);
        eps_k = (q / (1 - q)) * norm(x_k1 - x_k);
        x_k = x_k1;
    } while(eps_k > EPS);
    return std::make_pair(x_k[0], x_k[1]);
}



#endif //LAB2_2_FUNCTION_HPP
