#pragma once

#include "SVG_data.h"
#include "Complex.h"
#include "constants.h"
#include "Complex.h"
#include "complex_utilities.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>

void discrete_fourier_transform(Polygon figure, std::map<int, Complex>& coefficient) {
	std::ofstream outfile("coefficients.txt");
	for (int coefficient_index = MIN_FREQUENCY; coefficient_index <= MAX_FREQUENCY; coefficient_index++) {
		coefficient[coefficient_index] = Complex(0, 0);
		int i = 0;
		for (double _t = 0, _dt = 1 / (figure.size() * 1.0f); i < (int)figure.size(); _t += _dt, i++) {
			coefficient[coefficient_index] += 
				vertex_to_complex(figure[i]) * 
				exponentiate(Complex(0, -2 * M_PI * _t * coefficient_index)) * 
				_dt;
		}
		outfile << coefficient[coefficient_index].real << " + " << coefficient[coefficient_index].imaginary << "j" << " \n";
	}
	outfile.close();
}