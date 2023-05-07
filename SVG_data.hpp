#ifndef SVG_HPP
#define SVG_HPP

#include <SFML/Graphics.hpp>

class SVG_data { 
    public:
        char command;
        std::vector<sf::Vector2f> points;
        SVG_data() {};
        SVG_data(char command);
};

typedef std::vector<SVG_data> SVG_path_parameter;
typedef std::vector<sf::Vertex> Polygon;

#endif