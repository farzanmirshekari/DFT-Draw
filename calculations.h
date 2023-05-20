#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

inline float distance(float x_1, float y_1, float x_2, float y_2) {
    return std::sqrt(std::pow(x_2 - x_1, 2) + std::pow(y_2 - y_1, 2));
}

inline float distance(sf::Vector2f point_1, sf::Vector2f point_2) {
    return distance(point_1.x, point_1.y, point_2.x, point_2.y);
}

inline float square(float x) {
    return pow(x, 2);
}

inline float cube(float x) {
    return pow(x, 3);
}