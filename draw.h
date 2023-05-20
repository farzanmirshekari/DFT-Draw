#pragma once

#include "SVG_data.h"
#include "Arm.h"
#include "Complex.h"
#include "dft.h"
#include "calculations.h"
#include "SVG_utilities.h"

#include <SFML/Graphics.hpp>
#include <cmath>

double t = 0;

void generate_arms_from_coefficients(
    std::map<int, Complex> coefficients, 
    std::vector<Arm>& arms, 
    std::vector<sf::Vertex>& vertices, 
    std::vector<sf::CircleShape>& circles) {
        float phase, amplitude, frequency;

        vertices.push_back(sf::Vertex(sf::Vector2f(coefficients[0].real, coefficients[0].imaginary)));
        for (int i = MIN_FREQUENCY; i <= MAX_FREQUENCY; ++i) {
            if (i == 0) continue;

            frequency = i;
            amplitude  = sqrt(coefficients[i].real * coefficients[i].real + coefficients[i].imaginary * coefficients[i].imaginary);
            phase = atan(abs(coefficients[i].imaginary) / abs(coefficients[i].real));

            if      (coefficients[i].real > 0 && coefficients[i].imaginary < 0) phase *= -1.0f;
            else if (coefficients[i].real < 0 && coefficients[i].imaginary > 0) phase = M_PI - phase;
            else if (coefficients[i].real < 0 && coefficients[i].imaginary < 0) phase = M_PI + phase;

            arms.push_back(Arm(phase, frequency, amplitude));

            vertices.push_back(sf::Vertex(sf::Vector2f(), sf::Color(4, 75, 122)));

            sf::CircleShape circle;
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(1);
            circle.setOutlineColor(sf::Color(255, 255, 255, 50));

            circles.push_back(circle);
        }

        std::sort(arms.begin(), arms.end(), [](Arm const& a, Arm const& b) {return a.amplitude > b.amplitude; });
}

void update_vertices(
    std::vector<sf::Vertex>& curves, 
    std::vector<sf::Vertex>& vertices, 
    std::vector<sf::CircleShape>& circles, 
    std::vector<Arm>& arms) {
        int number_of_arms = arms.size();

        for (int i = 1; i <= number_of_arms; i++) {
            vertices[i].position.x = vertices[i - 1].position.x + arms[i - 1].amplitude * cos(t * 2 * M_PI * arms[i - 1].frequency + arms[i - 1].phase);
            vertices[i].position.y = vertices[i - 1].position.y + arms[i - 1].amplitude * sin(t * 2 * M_PI * arms[i - 1].frequency + arms[i - 1].phase);

            if (i > 1) {
                circles[i - 2].setRadius(distance(vertices[i].position, vertices[i - 1].position));
                circles[i - 2].setPosition(vertices[i - 1].position);
                circles[i - 2].setOrigin(circles[i - 2].getRadius(), circles[i - 2].getRadius());
            }
        }
        curves.push_back(sf::Vertex(sf::Vector2f(vertices[number_of_arms].position.x, vertices[number_of_arms].position.y), sf::Color(252, 140, 3)));

        if (curves.size() > (int)STORAGE_THRESHOLD) curves.erase(curves.begin());

        t += dt;
}

void initialize_drawing(
    std::string file_name,
    Polygon& coordinates,
    std::map<int, Complex>& coefficients,
    std::vector<Arm>& arms,
    std::vector<sf::Vertex>& vertices,
    std::vector<sf::CircleShape>& circles,
    float zoom,
    int x_offset,
    int y_offset) {
        std::string d_parameter = get_d_parameter_from_path(file_name);
        SVG_path_parameter path_parameter = convert_string_to_SVG_path(d_parameter, zoom);
        coordinates = convert_path_to_coordinates(path_parameter);

        discrete_fourier_transform(coordinates, coefficients);
        coefficients[0] = Complex(WIDTH / 2 + x_offset, HEIGHT / 2 + y_offset);
        generate_arms_from_coefficients(coefficients, arms, vertices, circles);
}

void draw(std::string file_name, float zoom, int x_offset, int y_offset) {
    std::vector<sf::Vertex> curves;
    curves.clear();
    std::vector<sf::Vertex> vertices;
    vertices.clear();
    std::vector<Arm> arms;
    arms.clear();
    std::map<int, Complex> coefficients;
    coefficients.clear();
    std::vector<sf::CircleShape> circles;
    circles.clear();
    std::map<int, sf::Text> coordinate_tags, frequency_tags;
    coordinate_tags.clear();
    frequency_tags.clear();
    Polygon coordinates;
    coordinates.clear();

    initialize_drawing(file_name, coordinates, coefficients, arms, vertices, circles, zoom, x_offset, y_offset);
    update_vertices(curves, vertices, circles, arms);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), file_name, sf::Style::Default, settings);
    window.setFramerateLimit(FRAME_RATE);

    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) 
            if (event.type == sf::Event::Closed) window.close();
        window.clear(sf::Color::Black);

        update_vertices(curves, vertices, circles, arms);

        if (!curves.empty()) 
            window.draw(&curves[0], curves.size(), sf::LineStrip);

		window.draw(&vertices[0], vertices.size(), sf::LineStrip);

        for (int i = 0; i < (int)circles.size(); ++i) {
            window.draw(circles[i]);
        }
		window.display();
    }
}