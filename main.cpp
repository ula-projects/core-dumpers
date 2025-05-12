#include <SFML/Graphics.hpp>
#include <Game.hpp>
#include <iostream>

int main()
{
    // SFML Window
    sf::RenderWindow window(sf::VideoMode({640, 640}), "Core Dumpers!");
    window.setFramerateLimit(60);
    // window.setVerticalSyncEnabled(true);

    // Game
    Game game;

    // Clock
    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        // Delta Time
        float dt = clock.reset().asSeconds();

        // if (dt < 0.0001f)
        //     continue;

        // Delta Time
        // if (dt < 0.0333f)
        //     dt = 0.0333f;

        std::cout << std::fixed << std::setprecision(7);
        // std::cout << dt << "\r" << std::flush;
        // Game Update
        game.update(dt);

        window.clear();

        // Game Draw updates
        game.draw(window);
        window.display();
    }
}
