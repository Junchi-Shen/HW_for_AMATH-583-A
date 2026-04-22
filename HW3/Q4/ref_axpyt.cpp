#include "ref_axpyt.hpp"
#include <iostream>
#include <vector>
#include <cmath>

int main() {
    // 简单校验逻辑
    std::vector<double> x = {1.0, 2.0};
    std::vector<double> y = {3.0, 4.0};
    axpy(2.0, x, y); // 预期结果: {5.0, 8.0}

    if (std::abs(y[0]-5.0) > 1e-12 || std::abs(y[1]-8.0) > 1e-12) {
        std::cerr << "AXPY Template Error!" << std::endl;
        return 1;
    }
    std::cout << "AXPY Template Success." << std::endl;
    return 0;
}