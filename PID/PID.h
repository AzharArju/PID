#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <chrono>
#include <ctime>
#include <functional>
#include <iostream>

static int window_width = 1600;

class PID {
    const float gravity = 9.81f;
    float Kp, Ki, Kd;
    float Proportional, Integral, Derivative;
    std::function<float()> dt;
    float error, prev_error, PID_out;
    float integral_limit = 5000.0f;
    float alpha = 0.1f;
    float mass;
    float output_limit = 5000.0f;
public:
    sf::CircleShape target = sf::CircleShape(10, 3);
    sf::RectangleShape plant = sf::RectangleShape(sf::Vector2f(20, 20));
    PID(float Kp, float Ki, float Kd, float error, float mass)
        : Kp(Kp), Ki(Ki), Kd(Kd), Integral(0), Proportional(0), Derivative(0), PID_out(0), error(error), prev_error(0), mass(mass) {
        target.setScale(.75, 1.5);
        target.setRotation(90);
        target.setPosition(550, error);
        target.setFillColor(sf::Color::Red);
        plant.setPosition(700, 880);
        dt = []() -> float {
            static auto startTime = std::chrono::steady_clock::now();
            auto currentTime = std::chrono::steady_clock::now();
            return static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count()) / 1000;
            };
    }
    float PIDcalc();
    void move();
};