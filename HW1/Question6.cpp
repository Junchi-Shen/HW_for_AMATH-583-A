#include <iostream>
#include <numeric> // For std::gcd

/**
 * @brief Checks if a linear Diophantine equation ax + by + cz = d has integer solutions.
 */
bool has_solution(int a, int b, int c, int target) {
    // Standard GCD for multiple numbers: gcd(a, b, c) = gcd(a, gcd(b, c))
    int common_divisor = std::gcd(a, std::gcd(b, c));
    
    std::cout << "GCD(" << a << ", " << b << ", " << c << ") = " << common_divisor << std::endl;
    
    // The theorem states: target must be divisible by the GCD of the coefficients
    return (target % common_divisor == 0);
}

int main() {
    int a = 6, b = 9, c = 15;
    int target = 107;

    std::cout << "Checking for solutions to " << a << "a + " << b << "b + " << c << "c = " << target << "..." << std::endl;

    if (has_solution(a, b, c, target)) {
        std::cout << "Result: Solutions exist." << std::endl;
    } else {
        std::cout << "Result: No integer solutions exist because " << target 
                  << " is not divisible by the GCD." << std::endl;
    }

    return 0;
}