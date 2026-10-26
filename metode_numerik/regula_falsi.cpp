// trying regula falsi
#include <iostream>
#include <cmath>
#include <iomanip>

// Define the function whose root needs to be found: f(x) = x^3 - x - 2
double f(double x) {
    return x * x * x - x - 2;
}

// Implements the Regula Falsi (False Position) Method
void regulaFalsi(double a, double b, double tolerance, int maxIterations) {
    // Check if the initial bracket is valid according to the Intermediate Value Theorem
    if (f(a) * f(b) >= 0) {
        std::cout << "Error: The function must have different signs at the boundaries a and b.\n";
        return;
    }

    double c = a; // Initialize the root estimate
    
    std::cout << std::setw(6) << "Iter" 
              << std::setw(12) << "a" 
              << std::setw(12) << "b" 
              << std::setw(12) << "c" 
              << std::setw(12) << "f(c)" << "\n";
    std::cout << std::string(54, '-') << "\n";

    for (int i = 1; i <= maxIterations; i++) {
        // Regula Falsi formula to calculate the next approximation
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));

        std::cout << std::setw(6) << i 
                  << std::setw(12) << std::fixed << std::setprecision(5) << a 
                  << std::setw(12) << b 
                  << std::setw(12) << c 
                  << std::setw(12) << f(c) << "\n";

        // Convergence check: If the absolute value of f(c) is within the tolerance threshold
        if (std::abs(f(c)) < tolerance) {
            std::cout << "\nRoot found at x = " << std::setprecision(6) << c << "\n";
            return;
        }

        // Decide the subinterval to check next
        if (f(c) * f(a) < 0) {
            b = c; // Root lies in the left subinterval [a, c]
        } else {
            a = c; // Root lies in the right subinterval [c, b]
        }
    }

    std::cout << "\nWarning: Maximum iterations reached. Estimated root = " << c << "\n";
}

int main() {
    // Initial interval [a, b] where f(a) and f(b) have opposite signs
    double a = 1.0;
    double b = 2.0;
    
    double tolerance = 0.0001;
    int maxIterations = 100;

    regulaFalsi(a, b, tolerance, maxIterations);

    return 0;
}
