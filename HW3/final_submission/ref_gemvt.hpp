#ifndef REF_GEMVT_HPP
#define REF_GEMVT_HPP

#include <vector>

template <typename T>
void gemv(T a, const std::vector<std::vector<T>> &A, const std::vector<T> &x, T b, std::vector<T> &y) {
    size_t m = A.size();
    size_t n = x.size();
    for (size_t i = 0; i < m; ++i) {
        T ax = 0;
        for (size_t j = 0; j < n; ++j) {
            ax += A[i][j] * x[j];
        }
        y[i] = a * ax + b * y[i];
    }
}

#endif