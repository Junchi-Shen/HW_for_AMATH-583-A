#ifndef REF_DAXPY_HPP
#define REF_DAXPY_HPP

#include <vector>

// 计算 y = a*x + y
void daxpy(double a, 
           const std::vector<double> &x, 
           std::vector<double> &y);
#endif