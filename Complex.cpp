#include "Complex.h"

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