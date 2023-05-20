#ifndef ARM_HPP
#define ARM_HPP 

class Arm {
    public:
        double phase, frequency, amplitude;
        Arm(double phase, double frequency, double amplitude);
        void set_parameters(double phase, double frequency, double amplitude);
        void set_phase(double phase);
        void set_frequency(double frequency);
        void set_amplitude(double amplitude);
};

#endif