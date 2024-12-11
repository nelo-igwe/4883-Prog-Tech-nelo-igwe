#include <iostream> // For standard input and output operations
#include <numeric>  // Provides utilities like std::gcd and other numeric operations

// Enable the use of standard library names without the 'std::' prefix
using namespace std;

class Fraction {  // Define a class to represent and manipulate fractions
private:  // Stores the numerator of the fraction
    int numerator;
    int denominator;   // Stores the denominator of the fraction (must not be zero)

public: 
    Fraction(int num, int den); // Constructor

    Fraction operator+(const Fraction&) const;   // Overloaded addition operator

    Fraction operator-(const Fraction&) const;  // Overloaded subtraction operator

    Fraction operator*(const Fraction&) const; // Overloaded multiplication operator

    Fraction operator/(const Fraction&) const;  // Overloaded division operator

    bool operator==(const Fraction&) const;  // Overloaded equality operator (==)

    friend ostream& operator<<(ostream& os, const Fraction& frac);   // Overload output operator (<<) for printing fractions

    void simplify();  // Function to simplify the fraction

    static int lcm(int a, int b);  // Utility functions for LCM and GCD
    static int gcd(int a, int b);
};

Fraction::Fraction(int num, int den) : numerator(num), denominator(den) {   // Implementation
    if (den == 0) {
        throw invalid_argument("Denominator cannot be zero");
    }
    simplify();  // Simplify upon construction
}

Fraction Fraction::operator+(const Fraction& other) const {
    int common_den = lcm(denominator, other.denominator);
    int num1 = numerator * (common_den / denominator);
    int num2 = other.numerator * (common_den / other.denominator);
    return Fraction(num1 + num2, common_den);
}

Fraction Fraction::operator-(const Fraction& other) const {
    int common_den = lcm(denominator, other.denominator);
    int num1 = numerator * (common_den / denominator);
    int num2 = other.numerator * (common_den / other.denominator);
    return Fraction(num1 - num2, common_den);
}

Fraction Fraction::operator*(const Fraction& other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

Fraction Fraction::operator/(const Fraction& other) const {
    if (other.numerator == 0) {
        throw std::invalid_argument("Cannot divide by zero");
    }
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

bool Fraction::operator==(const Fraction& other) const {       // Compare simplified versions of both fractions
    return numerator * other.denominator == other.numerator * denominator;
}

ostream& operator<<(ostream& os, const Fraction& frac) {
    os << frac.numerator << "/" << frac.denominator;
    return os;
}

void Fraction::simplify() {
    int gcd_value = gcd(numerator, denominator);
    numerator /= gcd_value;
    denominator /= gcd_value;
    if (denominator < 0) {  // Normalize fraction to keep denominator positive
        numerator = -numerator;
        denominator = -denominator;
    }
}

int Fraction::lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int Fraction::gcd(int a, int b) {
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int main() {  
// Main function for testing
    Fraction frac1(1, 2);
    Fraction frac2(3, 4);

    Fraction sum = frac1 + frac2;
    Fraction diff = frac1 - frac2;
    Fraction prod = frac1 * frac2;
    Fraction quot = frac1 / frac2;

    cout << "Sum: " << sum << endl;
    cout << "Difference: " << diff << endl;
    cout << "Product: " << prod << endl;
    cout << "Quotient: " << quot << endl;

    if (frac1 == frac2) {
        cout << "Fractions are equal" << endl;
    } else {
        cout << "Fractions are not equal" << endl;
    }

    return 0;
}
