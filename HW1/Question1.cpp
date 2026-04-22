// Question 1
#include "iostream"

int main(){

// SP (32-bit float)
    float epsilonF = 1.0f;
    while ((epsilonF + 1.0f) > 1.0f) {
        epsilonF = epsilonF / 2;
    }
    std::cout << "SP machine epsilon: " << epsilonF * 2 << std::endl;

    // DP (64-bit double)
    double epsilonD = 1.0;
    while ((epsilonD + 1.0) > 1.0) {
        epsilonD = epsilonD / 2;
    }
    std::cout << "DP machine epsilon: " << epsilonD * 2 << std::endl;

    return 0;  

}