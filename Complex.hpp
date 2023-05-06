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
};

#endif