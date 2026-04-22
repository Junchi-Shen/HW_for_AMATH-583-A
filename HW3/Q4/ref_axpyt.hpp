#ifndef REF_AXPYT_HPP
#define REF_AXPYT_HPP
#include <vector>

template <typename T>
void axpy(T a, const std::vector<T> &x, std::vector<T> &y) {
    for (size_t i = 0; i < x.size(); ++i) {
        y[i] = a * x[i] + y[i];
    }
}
#endif