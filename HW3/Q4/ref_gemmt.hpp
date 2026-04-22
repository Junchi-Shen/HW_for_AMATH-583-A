#ifndef REF_GEMMT_HPP
#define REF_GEMMT_HPP

#include <vector>

template <typename T>
void gemm(T a, const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B, T b, std::vector<std::vector<T>> &C) {
    size_t m = A.size();
    size_t p = A[0].size();
    size_t n = B[0].size();
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            T sum = 0;
            for (size_t k = 0; k < p; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = a * sum + b * C[i][j];
        }
    }
}

#endif