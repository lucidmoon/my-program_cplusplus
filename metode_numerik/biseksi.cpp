#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Define the function f(x) = x^2 - 5x + 6
double f(double x) {
    return (x * x) - (5 * x) + 6;
}

// Bisection method implementation
void bisection(double a, double b, double tolerance) {
    if (f(a) * f(b) >= 0) {
        cout << "Invalid interval. f(a) and f(b) must have opposite signs." << endl;
        return;
    }

    double c = a;
    int iteration = 0;

    cout << fixed << setprecision(6);
    cout << "Iter\t a\t\t b\t\t c (mid)\t f(c)\n";
    cout << "-------------------------------------------------------------------\n";

    while ((b - a) >= tolerance) {
        // Find the midpoint
        c = (a + b) / 2;

        cout << iteration << "\t " << a << "\t " << b << "\t " << c << "\t " << f(c) << "\n";

        // Check if the midpoint is the root or close enough
        if (f(c) == 0.0 || (b - a) / 2 < tolerance) {
            break;
        }

        // Decide the side to repeat the steps
        if (f(c) * f(a) < 0) {
            b = c;
        } else {
            a = c;
        }
        iteration++;
    }

    cout << "\nThe root is approximately: " << c << endl;
}

int main() {
    // Initial interval [a, b]
    // To find the root x = 2, we can use 0 and 2.5
    // To find the root x = 3, you could change this to 2.5 and 4
    double a = 0.0;
    double b = 2.5; 
    
    // Allowed error tolerance
    double tolerance = 0.0001;

    cout << "Finding root for f(x) = x^2 - 5x + 6\n\n";
    bisection(a, b, tolerance);

    return 0;
}