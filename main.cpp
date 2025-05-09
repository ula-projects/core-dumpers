#include <SFML/Graphics.hpp>
#include <Game.hpp>

int main()
{
    // SFML Window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML works!");
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
        game.update();

        window.display();
    }
}
