#pragma once

#include "Complex.hpp"

#include <cmath>
#include <iostream>

inline Complex operator*(Complex& a, Complex &b) {
    return Complex(a.real * b.real - a.imaginary * b.imaginary, a.real * b.imaginary + a.imaginary * b.real);
}

inline Complex operator*(Complex const a, Complex const b) {
    return Complex(a.real * b.real - a.imaginary * b.imaginary, a.real * b.imaginary + a.imaginary * b.real);
}

Complex operator+(Complex& a, Complex &b) {
    return Complex(a.real + b.real, a.imaginary + b.imaginary);
}

inline Complex operator+(Complex const a, Complex const b) {
    return Complex(a.real + b.real, a.imaginary + b.imaginary);
}

inline void operator+=(Complex& a, Complex &b) {
    a.real += b.real;
    a.imaginary += b.imaginary;
}

inline void operator+=(Complex& a, Complex const b) {
    a.real += b.real;
    a.imaginary += b.imaginary;
}

inline void operator*=(Complex& a, Complex &b) {
    a = Complex(a.real * b.real - a.imaginary * b.imaginary, a.real * b.imaginary + a.imaginary * b.real);
}

inline Complex operator*(Complex& a, double b) {
    return Complex(a.real * b, a.imaginary * b);
}

inline Complex operator*(Complex const a, double b) {
    return Complex(a.real * b, a.imaginary * b);
}

inline Complex operator+(Complex& a, double b) {
    return Complex(a.real + b, a.imaginary);
}

inline Complex operator+(Complex const a, double b) {
    return Complex(a.real + b, a.imaginary);
}

inline void operator*= (Complex& a, double b) {
    a.real *= b;
    a.imaginary *= b;
}

inline void operator+= (Complex& a, double b) {
    a.real += b;
}

inline void print(Complex a) {
    std::cout << a.real << " + " << a.imaginary << "i" << std::endl;
}


inline Complex vector_to_complex(sf::Vector2f point) {
	return Complex(point);
}

inline Complex vertex_to_complex(sf::Vertex point) {
	return Complex(point);
}

inline sf::Vector2f complex_to_vector(Complex number) {
	return number.get_vector();
}

inline Complex exponentiate(Complex c) {
	return Complex(cos(c.imaginary), sin(c.imaginary)) * exp(c.real);
}
