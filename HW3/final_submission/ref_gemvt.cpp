#include "ref_gemvt.hpp"
#include <iostream>
#include <vector>
#include <cmath>

int main() {
    float a = 1.0f, b = 0.0f;
    std::vector<std::vector<float>> A = {{1, 2}, {3, 4}};
    std::vector<float> x = {1, 1};
    std::vector<float> y = {0, 0};
    // 预期: {1*1+2*1, 3*1+4*1} = {3.0, 7.0}

    gemv(a, A, x, b, y);

    if (std::abs(y[0] - 3.0f) > 1e-6 || std::abs(y[1] - 7.0f) > 1e-6) {
        std::cerr << "ERROR: gemv template failed!" << std::endl;
        return 1;
    }
    std::cout << "gemv template passed." << std::endl;
    return 0;
}