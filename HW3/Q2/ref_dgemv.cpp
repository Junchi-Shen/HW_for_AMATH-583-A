#include "ref_dgemv.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>

void dgemv(double a, const std::vector<std::vector<double> > &A, 
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
int main() {
    const int ntrial = 3; 
    std::ofstream outfile("performance_dgemv.csv");
    outfile << "n,flops\n";


    {
        double alpha = 2.0;
        double beta = 1.0;
        std::vector<std::vector<double>> A_test = {{1.0, 2.0}, {3.0, 4.0}};
        std::vector<double> x_test = {5.0, 6.0};
        std::vector<double> y_test = {7.0, 8.0};

        dgemv(alpha, A_test, x_test, beta, y_test);

        if (std::abs(y_test[0] - 41.0) > 1e-12 || std::abs(y_test[1] - 86.0) > 1e-12) {
            std::cerr << "ERROR: dgemv implementation is incorrect!" << std::endl;
            return 1; // 发现错误退出
        } else {
            std::cout << "Correctness check passed." << std::endl;
        }
    }

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int n = 2; n <= 512; n++) {
        double alpha = 3.0;
        double beta  = 2.0;

        // 初始化数据
        std::vector<std::vector<double>> A(n, std::vector<double>(n));
        for(int i=0; i<n; ++i) 
            for(int j=0; j<n; ++j) A[i][j] = distribution(generator);
        
        std::vector<double> x(n, distribution(generator));
        std::vector<double> y(n, distribution(generator));

        double theoretical_flops = 2.0 * n * n;

        long double total_elapsed_time = 0.0L;

        // 测量 ntrial 次
        for (int t = 0; t < ntrial; ++t) {
            // 每次试验重新初始化 y，防止数值溢出或计算偏差（可选）
            auto start = std::chrono::high_resolution_clock::now();
            
            dgemv(alpha, A, x, beta, y);
            
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            total_elapsed_time += (duration.count() * 1.e-9); // 累加秒数
        }

        // 计算平均性能
        long double avg_time = total_elapsed_time / static_cast<long double>(ntrial);
        double flops_per_second = static_cast<double>(theoretical_flops / avg_time);

        outfile << n << "," << flops_per_second << "\n";
        
        if (n % 50 == 0) std::cout << "Finished size n = " << n << std::endl;
    }

    outfile.close();
    std::cout << "Results saved to performance_dgemv.csv" << std::endl;

    return 0;
}