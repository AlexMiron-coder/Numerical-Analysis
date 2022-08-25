#ifndef LAB3_1_POLYNOMIAL_HPP
#define LAB3_1_POLYNOMIAL_HPP

#include <vector>
#include <string>
#include "math.h"


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
class polynomial_t {
public:
    polynomial_t() : _n(0) {}

    explicit polynomial_t(size_t n) {
        _n = n;
        _data.resize(n);
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
                    out << (res[i] > 0 ? "" : "- ") << std::abs(res[i]) << "x" << up_pow(i) << " ";
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





#endif //LAB3_1_POLYNOMIAL_HPP
