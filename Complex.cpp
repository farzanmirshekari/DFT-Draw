#include "Complex.hpp"

#include <iostream>
#include <cmath>

Complex::Complex(sf::Vector2f point) {
    this->real = point.x;
    this->imaginary = point.y;
}

Complex::Complex(sf::Vertex point) {
    this->real = point.position.x;
    this->imaginary = point.position.y;
}

Complex::Complex(double real, double imaginary) {
    this->real = real;
    this->imaginary = imaginary;
}

sf::Vector2f Complex::get_vector() {
    return sf::Vector2f(this->real, this->imaginary);
}

Complex operator*(Complex a, Complex b) {
    return Complex(a.real * b.real - a.imaginary * b.imaginary, a.real * b.imaginary + a.imaginary * b.real);
}

Complex operator+(Complex a, Complex b) {
    return Complex(a.real + b.real, a.imaginary + b.imaginary);
}

Complex operator-(Complex a, Complex b) {
    return Complex(a.real - b.real, a.imaginary - b.imaginary);
}

Complex operator/(Complex a, Complex b) {
    return Complex((a.real * b.real + a.imaginary * b.imaginary) / (b.real * b.real + b.imaginary * b.imaginary), (a.imaginary * b.real - a.real * b.imaginary) / (b.real * b.real + b.imaginary * b.imaginary));
}

void operator*=(Complex &a, Complex b) {
    a = a * b;
}

void operator+=(Complex &a, Complex b) {
    a = a + b;
}

void operator-=(Complex &a, Complex b) {
    a = a - b;
}

void operator/=(Complex &a, Complex b) {
    a = a / b;
}

void Complex::print() {
    std::cout << this->real << " + " << this->imaginary << "i" << std::endl;
}

Complex Complex::vector_to_complex(sf::Vector2f point) {
    return Complex(point.x, point.y);
}

Complex Complex::vertex_to_complex(sf::Vertex point) {
    return Complex(point.position.x, point.position.y);
}

sf::Vector2f Complex::complex_to_vector(Complex complex) {
    return sf::Vector2f(complex.real, complex.imaginary);
}

Complex Complex::exponentiate() {
    return Complex(exp(this->real) * cos(this->imaginary), exp(this->real) * sin(this->imaginary));
}