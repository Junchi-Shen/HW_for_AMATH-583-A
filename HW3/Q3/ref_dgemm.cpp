#include "ref_dgemm.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include <cmath>


void dgemm(double a, const std::vector<std::vector<double>> &A,
           const std::vector<std::vector<double>> &B, double b,
           std::vector<std::vector<double>> &C) {
    size_t m = A.size();
    if (m == 0) return;
    size_t p = A[0].size();
    size_t n = B[0].size();

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < p; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = a * sum + b * C[i][j];
        }
    }
}

int main() {
    const int ntrial = 3;
    std::ofstream outfile("performance_dgemm.csv");
    outfile << "n,flops\n";


    {
        double alpha = 2.0;
        double beta = 0.5;
        std::vector<std::vector<double>> A_test = {{1.0, 2.0}, {3.0, 4.0}};
        std::vector<std::vector<double>> B_test = {{5.0, 6.0}, {7.0, 8.0}};
        std::vector<std::vector<double>> C_test = {{1.0, 1.0}, {1.0, 1.0}};

        
        dgemm(alpha, A_test, B_test, beta, C_test);

        if (std::abs(C_test[0][0] - 38.5) > 1e-12 || std::abs(C_test[1][1] - 100.5) > 1e-12) {
            std::cerr << "ERROR: dgemm implementation is incorrect!" << std::endl;
            return 1;
        } else {
            std::cout << "Correctness check passed." << std::endl;
        }
    }


    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int n = 2; n <= 512; n++) {
        double alpha = 1.0;
        double beta  = 1.0;

        // 初始化方阵
        std::vector<std::vector<double>> A(n, std::vector<double>(n));
        std::vector<std::vector<double>> B(n, std::vector<double>(n));
        std::vector<std::vector<double>> C(n, std::vector<double>(n));
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                A[i][j] = distribution(generator);
                B[i][j] = distribution(generator);
                C[i][j] = distribution(generator);
            }
        }


        double theoretical_flops = 2.0 * std::pow(n, 3);
        long double total_elapsed_time = 0.0L;

        for (int t = 0; t < ntrial; ++t) {
            auto start = std::chrono::high_resolution_clock::now();
            dgemm(alpha, A, B, beta, C);
            auto stop = std::chrono::high_resolution_clock::now();
            
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            total_elapsed_time += (duration.count() * 1.e-9);
        }

        long double avg_time = total_elapsed_time / static_cast<long double>(ntrial);
        double flops_per_second = static_cast<double>(theoretical_flops / avg_time);

        outfile << n << "," << flops_per_second << "\n";
        
        if (n % 50 == 0) std::cout << "Finished size n = " << n << std::endl;
    }

    outfile.close();
    return 0;
}