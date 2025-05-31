#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Settings.hpp"

int main()
{
    // SFML Window
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Core Dumpers!", sf::Style::Close);
    window.setFramerateLimit(60);

    // Game
    Settings::init();
    Game game;

    // Clock
    sf::Clock clock;
    float delta_time = 0.0f;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        std::cout << "FPS: " << 1 / delta_time << "    \r" << std::flush;

        delta_time = clock.restart().asSeconds();

        // Update
        game.update(delta_time, window);

        window.clear();

        // Update Graphics
        game.draw(window);

        window.display();
    }
}