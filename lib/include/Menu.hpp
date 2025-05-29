#pragma once

#include <SFML/Graphics.hpp>

class Menu
{
private:
    sf::Texture background_texture;
    sf::Sprite background;

    sf::Font font;
    sf::Text game_title;
    sf::Text game_start;

public:
    Menu();
    ~Menu();
    void mainMenuDraw(sf::RenderWindow &window);
    void mainMenuUpdate(sf::RenderWindow &window, int &game_state);
    void settingsMenu(sf::RenderWindow window);
};
