#include <SFML/Graphics.hpp>
#include <Game.hpp>
#include <iostream>

int main()
{
    // SFML Window
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Core Dumpers!");
    window.setFramerateLimit(60);

    // Game
    Game game;

    // Clock
    sf::Clock clock;
    float delta_time = 0.0f;

    sf::CircleShape circle(42.5);
    circle.setOrigin({42.5, 42.5});
    circle.setFillColor(sf::Color::Red);
    circle.setPosition({512, 512});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        // Update
        delta_time = clock.restart().asSeconds();
        game.update(delta_time, window);

        // Update Graphics
        window.clear();
        game.draw(window);
        window.display();
    }
}