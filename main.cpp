#include <SFML/Graphics.hpp>
#include <Game.hpp>

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    // SFML Window
    sf::RenderWindow window(sf::VideoMode({1024, 1024}), "Core Dumpers!");
    // Game
    Game game;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        // Game Update
        game.draw(window);

        window.display();
    }
}
