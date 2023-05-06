#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <SFML/Graphics.hpp>

class Complex {
    private:
        double real;
        double imaginary;

    public:
        Complex(sf::Vector2f point);
        Complex(sf::Vertex point);    
        Complex(double real, double imaginary);
        sf::Vector2f get_vector();
        friend Complex operator*(Complex a, Complex b);
        friend Complex operator+(Complex a, Complex b);
        friend Complex operator-(Complex a, Complex b);
        friend Complex operator/(Complex a, Complex b);
        friend void operator*=(Complex &a, Complex b);
        friend void operator+=(Complex &a, Complex b);
        friend void operator-=(Complex &a, Complex b);
        friend void operator/=(Complex &a, Complex b);
        void print();
        Complex vector_to_complex(sf::Vector2f point);
        Complex vertex_to_complex(sf::Vertex point);
        sf::Vector2f complex_to_vector(Complex complex);
        Complex exponentiate();
};

#endif