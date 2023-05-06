#ifndef ARM_HPP
#define ARM_HPP 

class Arm {
    private:
        double phase;
        double frequency;
        double amplitude;

    public:
        Arm(double phase, double frequency, double amplitude);
        void set_parameters(double phase, double frequency, double amplitude);
        void set_phase(double phase);
        void set_frequency(double frequency);
        void set_amplitude(double amplitude);
        double get_phase();
        double get_frequency();
        double get_amplitude();
};

#endif