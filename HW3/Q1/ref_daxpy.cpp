#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <fstream> 

void daxpy(double a, const std::vector<double> &x, std::vector<double> &y) {
    if (x.size() != y.size()) {
        std::cerr << "Error: Vector sizes do not match!" << std::endl;
        return;
    }
    for (size_t i = 0; i < x.size(); ++i) {
        y[i] = a * x[i] + y[i];
    }
}

int main() {
    const double a = 10.0;
    const int ntrial = 3;

    std::ofstream outfile("data.csv"); 
    outfile << "n,flops\n"; 

    for (int n = 2; n <= 512; ++n) {
        std::vector<double> x(n, 1.0);
        std::vector<double> y(n, 2.0);

        auto start = std::chrono::high_resolution_clock::now();
        for (int t = 0; t < ntrial; ++t) {
            daxpy(a, x, y);

        }
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> diff = end - start;
        double avg_time = diff.count() / ntrial;
        
        double flops = (2.0 * n) / avg_time;

        outfile << n << "," << flops << "\n";

        std::cout << n << " " << flops << "\n";
    }
    outfile.close();
    std::cout << "Data saved to data.csv" << std::endl;

    return 0;
}