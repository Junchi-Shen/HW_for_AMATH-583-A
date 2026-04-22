#include <iostream>

int main() {
    long long a = 200.0f;
    long long b = 300.0f;
    long long c = 400.0f;
    long long d = 500.0f; 
    long long product = a * b * c * d; // 使用 * 运算符

    std::cout << "The result is: " << product << std::endl;
    return 0;
}