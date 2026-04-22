
#include <iostream>

int main() {
    int a = 50000;
    
    // Expression 1: Multiplication happens first
    int result1 = (a * a) / a;
    
    // Expression 2: Division happens first
    int result2 = a * (a / a);
    
    std::cout << "(50000 * 50000) / 50000 = " << result1 << std::endl;
    std::cout << "50000 * (50000 / 50000) = " << result2 << std::endl;
    
    return 0;
}
