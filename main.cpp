#include <SFML/Graphics.hpp>
#include <Game.hpp>
#include <iostream>

int main()
{
    // SFML Window
    sf::RenderWindow window(sf::VideoMode({640, 640}), "Core Dumpers!");
    window.setFramerateLimit(60);

    // Game
    Game game;

    // Clock
    sf::Clock clock;
    float dt = 0.0f;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        // Delta Time
        dt = clock.restart().asSeconds();

        // Game Update
        game.update(dt);

        window.clear();
        // Game Draw updates
        game.draw(window);
        window.display();
    }
}
