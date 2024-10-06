#include <SFML/Graphics.hpp>
#include <iostream>

#include "PID.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(window_width, 900), "PID test.exe");
    window.setFramerateLimit(60);
    sf::Event event;
    PID _pid(0.2f, 0.2f, 2.0f, 200, 1.0f);

    while (window.isOpen()) {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        _pid.PIDcalc();
        _pid.move();

        window.clear();
        window.draw(_pid.target);
        window.draw(_pid.plant);
        window.display();
    }

    return 0;
}