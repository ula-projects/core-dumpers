#include <SFML/Graphics.hpp>
#include <Game.hpp>

int main()
{
    // SFML Window
    sf::RenderWindow window(sf::VideoMode({640, 640}), "Core Dumpers!");
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

        window.clear();
        // Game Update
        game.update(dt);
        // Game Draw updates
        game.draw(window);
        window.display();
    }
}
