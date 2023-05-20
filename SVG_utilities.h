#pragma once

#include "SVG_data.h"
#include "calculations.h"

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

std::string get_d_parameter_from_path(std::string file_name) {
    std::fstream file;
    file.open(file_name, std::fstream::in);

	enum STATE {
        FIND_PATH_TAG,
        FIND_D_PARAMETER,
        FIND_END_OF_D_PARAMETER,
        MERGING_LINES
    };
    STATE CURRENT_STATE = FIND_PATH_TAG;

	std::vector<std::string> lines;
    int d_position, a_position;
    std::string line;

	while (getline(file, line)) {
		switch (CURRENT_STATE) {
            case FIND_PATH_TAG:
                if ((int)line.find("<path") == -1) 
                    break;
                CURRENT_STATE = FIND_D_PARAMETER; /* intentional fall-through */

            case FIND_D_PARAMETER:
                d_position = line.find("d=\"");
                if (d_position == -1) 
                    break;

                while (d_position != -1 && d_position != 0 && line[d_position - 1] != ' ') {
                    line = line.substr(d_position + 3);
                    d_position = line.find("d=\"");
                }

                line = line.substr(d_position + 3);
                CURRENT_STATE = FIND_END_OF_D_PARAMETER; /* intentional fall-through */

            case FIND_END_OF_D_PARAMETER:
                a_position = line.find("\"");
                if (a_position == -1) {
                    lines.push_back(line);
                    break;
                }
                lines.push_back(line.substr(0, a_position));
                CURRENT_STATE = MERGING_LINES; /* intentional fall-through */

            case MERGING_LINES:
                line = "";
                for (int i = 0; i < (int)lines.size(); ++i)
                    line += lines[i];
                file.close();
                return line;

            default:
                assert(false);
                break;
        }
	}

    file.close();
    return "";
}

SVG_path_parameter convert_string_to_SVG_path(std::string input, float m_coefficient) {
    SVG_path_parameter path;
	std::string token = "";
	char command;
	int parameter_count = 0;
	float x_previous = 0, y_previous = 0;
	float x = 0, y = 0;

	for (int i = 0; i < (int)input.length(); ++i) {
		if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
			command = input[i];
			parameter_count = 0;
			x_previous = x;
            y_previous = y;
			path.push_back(SVG_data(command));
		}
		else if (input[i] == '-' || (input[i] >= '0' && input[i] <= '9')) {
			do {
				token += input[i++];
				if (input[i] == 'e') { 
					token += input[i++];
					if (input[i] == '-')
						token += input[i++];
				}						          
			} while (i < (int)input.length() && ((input[i] >= '0' && input[i] <= '9') || (input[i] == '.'))); 

			i--;

			if (command == 'h' || command == 'H') {
				x = stof(token);
				if (command == 'h')  x += x_previous;   
				                 x_previous = x;    
				path[path.size() - 1].points.push_back(sf::Vector2f(x * m_coefficient, y * m_coefficient));
				token = "";
				continue;
			}

			if (command == 'v' || command == 'V') {
				y = stof(token);
				if (command == 'v')  y += y_previous;  
								 y_previous = y;  
				path[path.size() - 1].points.push_back(sf::Vector2f(x * m_coefficient, y * m_coefficient));
				token = "";
				continue;
			}

			if (((command == 'c' || command == 'C') && parameter_count % 6 == 0 && parameter_count > 0) ||
				((command == 'q' || command == 'Q') && parameter_count % 4 == 0 && parameter_count > 0)) {
				x_previous = x; 
                y_previous = y;
				path.push_back(SVG_data(command));
			}

			if (parameter_count % 2 == 0) x = stof(token);
			else {
				y = stof(token); 
				if (command >= 'a' && command <= 'z') {
                    x += x_previous;
                    y += y_previous;
                }
				if (command == 'l') {             
                    x_previous = x;
                    y_previous = y;
                }
				path[path.size() - 1].points.push_back(sf::Vector2f(x * m_coefficient, y * m_coefficient));
			}
		
			parameter_count++;
			token = "";
		}
	}

	return path;
}

Polygon convert_path_to_coordinates(SVG_path_parameter path) {
    if (path.empty()) return Polygon();

    Polygon image;
    sf::Vector2f current_point;
    sf::Vector2f end_point;
    sf::Vector2f bezier_point_1;
    sf::Vector2f bezier_point_2;

    const float _dt = 0.01;
    int i, j;
    float _t;

    for (i = 0; i < (int)path.size(); ++i) {
        switch (path[i].command) {
            case 'M':
            case 'm':
            case 'L':
            case 'l':
            case 'H':
            case 'h':
            case 'V':
            case 'v': {
                j = 0;
                if (i == 0) {
                    current_point = path[i].points[0];
                    image.push_back(sf::Vertex(current_point));
                    j++;
                }

                for (; j < (int)path[i].points.size(); ++j) {
                    end_point = path[i].points[j];

                    for (_t = 0; _t < 1; _t += _dt) 
					    image.push_back(sf::Vertex(sf::Vector2f((1 - _t) * current_point + _t * end_point)));

				    current_point = end_point;
                }
                break;
            }
            case 'Q':
            case 'q': {
                bezier_point_1 = path[i].points[0];
                end_point = path[i].points[1];

                for (_t = 0; _t < 1; _t += _dt) 
                    image.push_back(sf::Vertex(sf::Vector2f(square(1 - _t) * current_point + 2 * (1 - _t) * _t * bezier_point_1 + square(_t)* end_point)));

                current_point = end_point;
                break;
            }
            case 'C':
            case 'c': {
                bezier_point_1 = path[i].points[0];
                bezier_point_2 = path[i].points[1];
                end_point     = path[i].points[2];

                for (_t = 0; _t < 1; _t += _dt)
                    image.push_back(sf::Vertex(sf::Vector2f(cube(1 - _t) * current_point + 3 * square(1 - _t) * _t * bezier_point_1 + 3 * (1 - _t) * square(_t) * bezier_point_2 + cube(_t) * end_point)));

                current_point = end_point;
                break;
            }
            case 'Z':
            case 'z': {
                end_point = path[0].points[0];
                for (_t = 0; _t < 1; _t += _dt)
                    image.push_back(sf::Vertex(sf::Vector2f((1 - _t) * current_point + _t * end_point)));

                break;
            }
            default:
                assert(false);
                break;
        }
    }

	return image;
}