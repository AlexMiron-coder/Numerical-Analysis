#include "matrix.hpp"
#include <vector>

template <class T>
class system_solver {
public:
	std::vector<T> arnoldi_iteration(matrix_t<T>, std::vector<T>);

private:
	matrix_t<T> a;
};

template<class T>
std::vector<T> system_solver<T>::arnoldi_iteration(matrix_t<T> a, std::vector<T> b) {
	size_t n = b.size();
	size_t m = a[0].size();

	matrix_t<T> h(n + 1, n);
	matrix_t<T> q(m, n + 1);
	T _q = b / norm_vec(b);
	for (size_t i = 0; i < b.size(); i++) {
		q[i][0] = b[i];
	}

	for (size_t k = 0; k < n; k++) {
		T v = scalar(a, q);
	}
}