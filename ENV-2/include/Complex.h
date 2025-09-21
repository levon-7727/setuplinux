#pragma once

#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imag;
public:
    Complex(double real = 0.0, double imag = 0.0);

    double getReal() const;
    double getImag() const;
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(double scalar) const;
    double abs() const;

};
