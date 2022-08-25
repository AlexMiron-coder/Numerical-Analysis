#ifndef LAB3_3_NUMERICAL_H
#define LAB3_3_NUMERICAL_H


#include <iostream>
#include <vector>
#include "math.h"
#include <string>



std::string up_pow(int num) {
    std::string ans = "";
    while (num > 0) {
        switch (num % 10) {
            case 0:
                ans += "\u2070";
                break;
            case 1:
                ans += "\u00b9";
                break;
            case 2:
                ans += "\u00b2";
                break;
            case 3:
                ans += "\u00b3";
                break;
            case 4:
                ans += "\u2074";
                break;
            case 5:
                ans += "\u2075";
                break;
            case 6:
                ans += "\u2076";
                break;
            case 7:
                ans += "\u2077";
                break;
            case 8:
                ans += "\u2078";
                break;
            case 9:
                ans += "\u2079";
                break;
        }
        num = num / 10;
    }
    return ans;
}


template<class T>
std::vector<T> operator + (const std::vector<T> &lhs, const std::vector<T> &rhs) {
    std::vector<T> result(lhs.size());
    for (size_t i = 0; i < lhs.size(); i++) {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

template<class T>
std::vector<T> operator - (const std::vector<T> &lhs, const std::vector<T> &rhs) {
    std::vector<T> result(lhs.size());
    for (size_t i = 0; i < lhs.size(); i++) {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}


namespace snm {
    template<class T>
    class matrix_t{
    public:
        matrix_t() {
            _n = 0, _m = 0;
            _data = std::vector<std::vector<T>>();
        }

        explicit matrix_t(size_t n) {
            _n = n, _m = n;
            _data = std::vector<std::vector<T>>(n, std::vector<T>(n, 0));
        }

        matrix_t(size_t n, size_t m) {
            _n = n, _m = m;
            _data = std::vector<std::vector<T>>(n, std::vector<T>(m));
        }

        void identity() {
            _data = std::vector<std::vector<T>>(_n, std::vector<T>(_m, 0));
            for (size_t i = 0; i < _n; i++) {
                _data[i][i] = 1;
            }
        }

        matrix_t<T> transpose() {
            matrix_t<T> transposed_m(_m, _n);
            for(int i = 0; i < _n; i++) {
                for (int j = 0; j < _m; j++) {
                    transposed_m[j][i] = _data[i][j];
                }
            }
            return transposed_m;
        }

        void push_matrix() {
            for (size_t i = 0; i < _n; i++) {
                for (size_t j = 0; j < _m; j++) {
                    std::cin >> _data[i][j];
                }
            }
        }

        void write_matrix() {
            for (size_t i = 0; i < _n; i++) {
                for (size_t j = 0; j < _m; j++) {
                    std::cout << _data[i][j] << " ";
                }
                std::cout << "\n";
            }
        }

        bool is_empty() {
            if (_data.empty())
                return true;
            return false;
        }

        size_t size() {
            return _n;
        }

        std::vector<T>& operator [](size_t index) {
            return _data[index];
        }

        friend std::vector<T> operator * (matrix_t<T> &mat, std::vector<T> &vec) {
            std::vector<T> result(vec.size(), 0);
            T res = 0;
            for (size_t i = 0; i < mat._n; i++) {
                for (size_t j = 0; j < mat._m; j++) {
                    result[i] += mat[i][j] * vec[j];
                }
            }
            return result;
        }

        friend matrix_t<T> operator * (matrix_t<T> &a, matrix_t<T> &b) {
            //size_t n = a.size();
            matrix_t<T> result(a._n, b._m);
            for (size_t i = 0; i < a._n; i++) {
                for (size_t j = 0; j < b._m; j++) {
                    for (size_t k = 0; k < a._m; k++) {
                        result[i][j] += a[i][k] * b[k][j];
                    }
                }
            }
            return result;
        }
    private:
        size_t _n;
        size_t _m;
        std::vector<std::vector<T>> _data;
    };


    template<class T>
    class lu {
    public:
        static std::vector<T> solve(matrix_t<T> a, std::vector<T> b) {
            matrix_t<T> l, u;
            lu_decomposition(a, l, u);
            size_t n = a.size();
            std::vector<T> x(n, 0);
            std::vector<T> z(n, 0);
            T sum = 0;
            for (size_t i = 0; i < n; i++) {
                for (size_t j = 0; j < i; j++) {
                    sum += l[i][j] * z[j];
                }
                z[i] = b[i] - sum;
                sum = 0;
            }
            for (size_t i = n - 1; i >= 0; i--) {
                for (size_t j = i + 1; j < n; j++) { // n
                    sum += u[i][j] * x[j];
                }
                x[i] = (z[i] - sum) / u[i][i];
                sum = 0;
                if (i == 0) break;
            }
            return x;
        }
    private:
        static void lu_decomposition(matrix_t<T> &a, matrix_t<T> &l, matrix_t<T> &u) {
            if (a.is_empty()) return;
            u = a; l = a;

            for (size_t i = 0; i < a.size(); i++) {
                for (size_t j = i; j < a.size(); j++) {
                    l[j][i] = u[j][i] / u[i][i];
                }
            }
            for (size_t k = 1; k < a.size(); k++) {
                for (size_t i = k - 1; i < a.size(); i++) {
                    for (size_t j = i; j < a.size(); j++) {
                        l[j][i] = u[j][i] / u[i][i];
                    }
                }
                for (size_t i = k; i < a.size(); i++) {
                    for (size_t j = k - 1; j < a.size(); j++) {
                        u[i][j] = u[i][j] - l[i][k - 1] * u[k - 1][j];
                    }
                }
            }
        }
    };



    template<class T>
    class polynomial_t {
    public:
        polynomial_t() : _n(0) {}

        explicit polynomial_t(size_t n) {
            _n = n;
            _data.resize(n);
        }

        polynomial_t(const std::vector<T> &vec) {
            _data = vec;
            _n = vec.size();
        }

        size_t size() const {
            return this->_n;
        }

        T& operator [](size_t index) {
            return _data[index];
        }

        const T& operator [] (size_t index) const {
            return _data[index];
        }

        void pop_back() {
            if (_n > 0) {
                _data.pop_back();
                _n--;
                return;
            }
            throw std::runtime_error("vector is empty\n");
        }

        T back() {
            if (_n > 0) {
                return _data.back();
            }
            throw std::runtime_error("vector is empty\n");
        }

        T operator () (T x) {
            T result = 0;
            for (size_t i = 0; i < _n; i++) {
                result += _data[i] * pow(x, i);
            }
            return result;
        }

        polynomial_t<T>& operator = (const polynomial_t<T> &rhs) {
            _n = rhs.size();
            _data = rhs._data;
            return *this;
        }

        friend polynomial_t<T> operator * (const polynomial_t<T> &lhs, const polynomial_t<T> &rhs) {
            polynomial_t<T> result(lhs.size() + rhs.size());
            for (size_t i = 0; i < lhs.size(); i++) {
                for (size_t j = 0; j < rhs.size(); j++) {
                    result[i + j] += lhs[i] * rhs[j];
                }
            }
            while (result.size() > 0 and result.back() == 0) {
                result.pop_back();
            }
            return result;
        }

        friend polynomial_t<T> operator + (const polynomial_t<T> &lhs, const polynomial_t<T> &rhs) {
            size_t min_size = std::min(lhs.size(), rhs.size());
            size_t max_size = std::max(lhs.size(), rhs.size());
            polynomial_t<T> result(max_size);

            for (size_t i = 0; i < min_size; i++) result[i] = lhs[i] + rhs[i];
            if (lhs.size() < rhs.size()) {
                for (size_t i = min_size; i < max_size; i++) result[i] = rhs[i];
            } else {
                for (size_t i = min_size; i < max_size; i++) result[i] = lhs[i];
            }

            while (result.size() > 0 and result._data.back() == 0) {
                result.pop_back();
            }
            return result;
        }

        friend polynomial_t<T> operator * (const polynomial_t<T> &lhs, const T &num) {
            polynomial_t<T> result(lhs.size());
            for (size_t i = 0; i < lhs.size(); i++) {
                result[i] = lhs[i] * num;
            }
            while (result.size() > 0 and result._data.back() == 0) {
                result.pop_back();
            }
            return result;
        }

        friend std::ostream& operator << (std::ostream& out, const polynomial_t<T>& res) {
            for (long int i = res.size() - 1; i >= 0; i--) {
                if (i == res.size() - 1) {
                    if (res[i] != 0) {
                        if (i == 1) {
                            out << (res[i] > 0 ? "" : "- ") << std::abs(res[i]) << "x ";
                        } else {
                            out << (res[i] > 0 ? "" : "- ") << std::abs(res[i]) << "x" << up_pow(i) << " ";
                        }
                    }
                    continue;
                } else if (i == 0) {
                    if (res[i] != 0 and std::abs(res[i]) != 1) {
                        out << (res[i] > 0 ? "+ " : "- ") << std::abs(res[i]) << " ";
                    } else if (std::abs(res[i]) == 1) {
                        out << (res[i] > 0 ? "1 " : "- 1");
                    }
                    continue;
                } else if (i == 1) {
                    if (res[i] != 0 and std::abs(res[i]) != 1) {
                        out << (res[i] > 0 ? "+ " : "- ") << std::abs(res[i]) << "x ";
                    } else if (std::abs(res[i]) == 1) {
                        out << (res[i] > 0 ? "x " : "- x");
                    }
                    continue;
                } else {
                    if (res[i] != 0 and std::abs(res[i]) != 1) {
                        out << (res[i] > 0 ? "+ " : "- ") << std::abs(res[i]) << "x" << up_pow(i) << " ";
                    } else if (std::abs(res[i]) == 1) {
                        out << (res[i] > 0 ? "x" : "- x") << up_pow(i) << " ";
                    }
                }
            }
            return out;
        }
    private:
        std::vector<T> _data;
        size_t _n;
    };
}






#endif //LAB3_3_NUMERICAL_H
