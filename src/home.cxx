#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace sf;

void home() {
    RenderWindow window(VideoMode(600, 600), "Hello From SFML");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Magenta);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
}