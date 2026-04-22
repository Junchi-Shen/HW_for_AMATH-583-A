#include "ref_daxpy.hpp"
#include <iostream>

void daxpy(double a, const std::vector<double> &x, std::vector<double> &y) {
    if (x.size() != y.size()) {
        std::cerr << "Error: Vector sizes do not match!" << std::endl;
        return;
    }
    for (size_t i = 0; i < x.size(); ++i) {
        y[i] = a * x[i] + y[i];
    }
}
