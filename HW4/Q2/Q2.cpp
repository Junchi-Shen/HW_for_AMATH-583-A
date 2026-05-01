#include <iostream>


#include <vector>


template<typename T>
void mm_kij(T a, const std::vector<T>& A, const std::vector<T>& B, T b,
            std::vector<T>& C, int m, int p, int n) {
    

    for (int i = 0; i < m * n; ++i) {
        C[i] *= b;
    }


    for (int k = 0; k < p; ++k) {
        for (int i = 0; i < m; ++i) {

            T aik = a * A[i * p + k]; 
            for (int j = 0; j < n; ++j) {
                C[i * n + j] += aik * B[k * n + j];
            }
        }
    }
}


template<typename T>
void mm_jki(T a, const std::vector<T>& A, const std::vector<T>& B, T b,
            std::vector<T>& C, int m, int p, int n) {
    
    for (int i = 0; i < m * n; ++i) C[i] *= b;

    for (int j = 0; j < n; ++j) {
        for (int k = 0; k < p; ++k) {
            T bkj = a * B[k * n + j]; // 提取最内层不变的部分
            for (int i = 0; i < m; ++i) {
                C[i * n + j] += A[i * p + k] * bkj;
            }
        }
    }
}

template<typename T>
void run_benchmark(int n, int ntrial, std::string label ){
    T alpha = 1.0, beta = 0.0;
    std::vector<T> A(n * n, 1.1), B(n * n, 1.2), C(n * n, 0.0);

    auto start_kij = std::chrono::high_resolution_clock::now();
    for (int t = 0; t < ntrial; ++t) {
        mm_kij(alpha, A, B, beta, C, n, n, n);
    };
    auto end_kij = std::chrono::high_resolution_clock::now();


    std::fill(C.begin(), C.end(), 0.0); 


    auto start_jki = std::chrono::high_resolution_clock::now();
    for (int t = 0; t < ntrial; ++t) {
        mm_jki(alpha, A, B, beta, C, n, n, n);
    }
    auto end_jki = std::chrono::high_resolution_clock::now();


    double time_kij = std::chrono::duration<double>(end_kij - start_kij).count() / ntrial;
    double time_jki = std::chrono::duration<double>(end_jki - start_jki).count() / ntrial;


    double gflops_kij = (2.0 * n * n * n) / time_kij / 1e9;
    double gflops_jki = (2.0 * n * n * n) / time_jki / 1e9;


    std::cout << n << ", " << label << ", " << gflops_kij << ", " << gflops_jki << std::endl;

}

int main(){
    int ntrial = 5;

    std::cout << "n, type, kij_GFLOPs, jki_GFLOPs" << std::endl;

    for (int n : {2, 4, 8, 16, 32, 64, 128, 256, 512}) {
        // 分别跑 float 和 double
        run_benchmark<float>(n, ntrial, "FP32");
        run_benchmark<double>(n, ntrial, "FP64");
    }

    return 0;
}