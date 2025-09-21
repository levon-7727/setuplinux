#include "Complex.h"
#include <cmath>

Complex::Complex(double real, double imag)
  : real(real), imag(imag)
{}

double Complex::getReal() const { return real; }
double Complex::getImag() const { return imag; }

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(double scalar) const {
    return Complex(real * scalar, imag * scalar);
}

double Complex::abs() const {
    return std::sqrt(real * real + imag * imag);
}

