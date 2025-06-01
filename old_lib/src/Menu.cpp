#include <Menu.hpp>
#include <iostream>

Menu::Menu() : background(background_texture), game_title(font), game_start(font)
{

    if (!background_texture.loadFromFile("./assets/textures/nebula-3.png"))
    {
    }
    background.setTextureRect({{0, 0}, {1024, 1024}});
    background.setOrigin({512, 512});
    background.setPosition({400, 400});

    if (!font.openFromFile("./assets/fonts/PixelOperator8.ttf"))
    {
    }
    game_title.setFont(font);
    game_title.setString("Core Dumpers!");
    game_title.setCharacterSize(50);
    game_title.setFillColor({157, 0, 255});
    game_title.setOutlineColor(sf::Color::White);
    game_title.setOutlineThickness(2);
    sf::Vector2f title_bounds = game_title.getGlobalBounds().size;
    game_title.setOrigin({title_bounds.x / 2, title_bounds.y / 2});
    game_title.setPosition({400, 300});

    game_start.setString("Start Game");
    game_start.setCharacterSize(32);
    game_start.setFillColor(sf::Color::White);
    game_start.setOutlineColor({157, 0, 255});
    sf::Vector2f start_bounds = game_start.getGlobalBounds().size;
    game_start.setOrigin({start_bounds.x / 2, title_bounds.y / 2});
    game_start.setPosition({400, 400});
    game_start.setOutlineColor(sf::Color::White);
}

Menu::~Menu()
{
}

void Menu::mainMenuDraw(sf::RenderWindow &window)
{

    window.draw(background);
    window.draw(game_title);
    window.draw(game_start);
}

void Menu::mainMenuUpdate(sf::RenderWindow &window, int &game_state)
{
    sf::Vector2f mouse_pos({static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y)});

    if (game_start.getGlobalBounds().contains(mouse_pos))
    {
        game_start.setFillColor({157, 0, 255});
        game_start.setOutlineThickness(2);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && game_state == 0)
        {
            // Iniciamos el juego
            game_state = 1;
        }
    }
    else
    {
        game_start.setFillColor(sf::Color::White);
        game_start.setOutlineThickness(0);
    }
};
