#include <vector>


template<class T>
T norm_vec(std::vector<T> vector) {
    T max_vector = std::abs(vector[0]);
    for (size_t i = 1; i < vector.size(); i++) {
        if (std::abs(vector[i]) > max_vector) max_vector = abs(vector[i]);
    }
    return max_vector;
}

template<class T>
T scalar(matrix_t<T> mat, std::vector<T> vec) {
    T ans = 0;
    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat[i].size(); j++) {
            ans += mat[j][i] * vec[i];
        }
    }
    return ans;
}



template<class T>
class matrix_t {
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
        _data = std::vector<std::vector<T>>(n, std::vector<T>(m, 0));
    }

    void identity() {
        _data = std::vector<std::vector<T>>(_n, std::vector<T>(_m, 0));
        for (size_t i = 0; i < _n; i++) {
            _data[i][i] = 1;
        }
    }

    matrix_t<T> transpose() {
        matrix_t<T> transposed_m(_m, _n);
        for (int i = 0; i < _n; i++) {
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

    friend std::vector<T> operator * (matrix_t<T>& mat, std::vector<T>& vec) {
        std::vector<T> result(vec.size(), 0);
        T res = 0;
        for (size_t i = 0; i < mat._n; i++) {
            for (size_t j = 0; j < mat._m; j++) {
                result[i] += mat[i][j] * vec[j];
            }
        }
        return result;
    }

    friend matrix_t<T> operator * (matrix_t<T>& a, matrix_t<T>& b) {
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