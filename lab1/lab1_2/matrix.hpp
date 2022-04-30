#ifndef LAB1_2_MATRIX_HPP
#define LAB1_2_MATRIX_HPP


#include <vector>

template<class T>
class Matrix{
public:
    Matrix();
    explicit Matrix(size_t);
    void push_matrix();
    bool isEmpty();
    size_t size();
    std::vector<T>& operator [](size_t);
    Matrix<T>& operator = (const Matrix<T> &);
private:
    size_t _size;
    std::vector<std::vector<T>> _data;
};


// Implementation
template<class T>
Matrix<T>::Matrix(size_t n) {
    _size = n;
    //_data.resize(n);
    _data = std::vector<std::vector<T>>(n, std::vector<T>(n));
}

template<class T>
Matrix<T>::Matrix() {
    _size = 0;
    _data = std::vector<std::vector<T>>();
}

template<class T>
std::vector<T> &Matrix<T>::operator[](size_t index) {
    return _data[index];
}

template<class T>
size_t Matrix<T>::size() {
    return _size;
}

template<class T>
bool Matrix<T>::isEmpty() {
    if (_data.empty())
        return true;
    return false;
}

template<class T>
void Matrix<T>::push_matrix() {
    for (size_t i = 0; i < _size; i++) {
        for (size_t j = 0; j < _size; j++) {
            std::cin >> _data[i][j];
        }
    }
}

template<class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix) {
    _size = matrix._size;
    _data = matrix._data;
    return *this;
}





#endif //LAB1_2_MATRIX_HPP
