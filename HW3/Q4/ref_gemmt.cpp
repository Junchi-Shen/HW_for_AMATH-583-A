#include "ref_gemmt.hpp"
#include <iostream>
#include <vector>
#include <cmath>

int main() {
    double a = 1.0, b = 1.0;
    std::vector<std::vector<double>> A = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> B = {{5, 6}, {7, 8}};
    std::vector<std::vector<double>> C = {{1, 1}, {1, 1}};
    // AB = {{19, 22}, {43, 50}}
    // 1*AB + 1*C = {{20, 23}, {44, 51}}

    gemm(a, A, B, b, C);

    if (std::abs(C[0][0] - 20.0) > 1e-12 || std::abs(C[1][1] - 51.0) > 1e-12) {
        std::cerr << "ERROR: gemm template failed!" << std::endl;
        return 1;
    }
    std::cout << "gemm template passed." << std::endl;
    return 0;
}