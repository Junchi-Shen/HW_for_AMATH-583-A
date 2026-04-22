#include "ref_dgemv.hpp"
#include <iostream>

void dgemv(double a, const std::vector<std::vector<double>> &A,
           const std::vector<double> &x, double b, std::vector<double> &y) {
    size_t m = A.size();
    size_t n = x.size();

    for (size_t i = 0; i < m; ++i) {
        double ax = 0.0;
        for (size_t j = 0; j < n; ++j) {
            ax += A[i][j] * x[j];
        }
        y[i] = a * ax + b * y[i];
    }
}
