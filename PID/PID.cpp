#include "PID.h"

float PID::PIDcalc() {
    prev_error = error;
    error = plant.getPosition().y - target.getPosition().y;
    Proportional = error * Kp;
    if (dt() > .25) {
        float unfiltered_derivative = (error - prev_error) / dt();
        Derivative = alpha * unfiltered_derivative + (1 - alpha) * Derivative;
        Integral += error * dt();
    }
    if (Integral > integral_limit) { Integral = integral_limit; }
    if (Integral < -integral_limit) { Integral = -integral_limit; }
    PID_out = ((Proportional + (Integral * Ki) + (Derivative * Kd)) - gravity) / mass;
    if (PID_out > output_limit) { PID_out = output_limit; }
    if (PID_out < -output_limit) { PID_out = -output_limit; }
    return PID_out;
}


void PID::move() {
    plant.move(0, -(PID_out));
    std::cout << error << ' ' << dt() << '\n';
    std::cout << Integral << '\n';
}