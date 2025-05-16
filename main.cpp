#include <SFML/Graphics.hpp>
#include <Game.hpp>
#include <iostream>

int main()
{
    // SFML Window
    sf::RenderWindow window(sf::VideoMode({640, 640}), "Core Dumpers!");
    window.setFramerateLimit(60);
    sf::Texture texture;
    if (!texture.loadFromFile("./assets/textures/space1.png"))
    {
    }
    sf::Sprite background(texture);
    background.setTextureRect({{0, 0}, {493, 493}});
    background.setOrigin({246.5f, 246.5f});
    background.setScale({2, 2});
    background.setPosition({0, 0});

    sf::CircleShape origin(42.5);
    origin.setOrigin({42.5, 42.5});
    origin.setPosition({0, 0});
    origin.setFillColor(sf::Color::Red);
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
        window.draw(background);
        game.draw(window);
        window.draw(origin);
        window.display();
    }
}
