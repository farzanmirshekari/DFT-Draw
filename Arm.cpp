#include "Arm.hpp"

Arm::Arm(double phase, double frequency, double amplitude) {
    this->phase = phase;
    this->frequency = frequency;
    this->amplitude = amplitude;
}

void Arm::set_parameters(double phase, double frequency, double amplitude) {
    this->phase = phase;
    this->frequency = frequency;
    this->amplitude = amplitude;
}

void Arm::set_phase(double phase) {
    this->phase = phase;
}

void Arm::set_frequency(double frequency) {
    this->frequency = frequency;
}

void Arm::set_amplitude(double amplitude) {
    this->amplitude = amplitude;
}

double Arm::get_phase() {
    return this->phase;
}

double Arm::get_frequency() {
    return this->frequency;
}

double Arm::get_amplitude() {
    return this->amplitude;
}