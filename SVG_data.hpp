#ifndef SVG_HPP
#define SVG_HPP

#include <SFML/Graphics.hpp>

class SVG_data {
    private:
        char command;
        std::vector<sf::Vector2f> points;
    
    public:
        SVG_data(char command);
        char get_command();
};

typedef std::vector<SVG_data> SVG_path_parameter;
typedef std::vector<sf::Vertex> Polygon;

#endif