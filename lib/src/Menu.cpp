#include <Menu.hpp>

Menu::Menu() : game_title(Settings::fonts["pixel"]), game_start(Settings::fonts["pixel"])
{

    game_title.setString("Core Dumpers!");
    game_title.setCharacterSize(50);
    game_title.setFillColor({157, 0, 255});
    game_title.setOutlineColor(sf::Color::White);
    game_title.setOutlineThickness(2);
    sf::Vector2f title_bounds = game_title.getGlobalBounds().size;
    game_title.setOrigin({title_bounds.x / 2, title_bounds.y / 2});
    game_title.setPosition({Settings::SCREEN_WIDTH / 2, Settings::SCREEN_HEIGHT / 3});

    game_start.setString("Start Game");
    game_start.setCharacterSize(32);
    game_start.setFillColor(sf::Color::White);
    game_start.setOutlineColor({157, 0, 255});
    sf::Vector2f start_bounds = game_start.getGlobalBounds().size;
    game_start.setOrigin({start_bounds.x / 2, title_bounds.y / 2});
    game_start.setPosition({Settings::SCREEN_WIDTH / 2, Settings::SCREEN_HEIGHT / 2});
    game_start.setOutlineColor(sf::Color::White);
}

Menu::~Menu()
{
}

void Menu::mainMenuDraw(sf::RenderWindow &window)
{
    window.draw(game_title);
    window.draw(game_start);
}

void Menu::mainMenuUpdate(sf::RenderWindow &window, GameState &game_state)
{
    sf::Vector2f mouse_pos({static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y)});

    if (game_start.getGlobalBounds().contains(mouse_pos))
    {
        game_start.setFillColor({157, 0, 255});
        game_start.setOutlineThickness(2);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && game_state == GameState::MainMenu)
        {
            game_state = GameState::Loading;
        }
    }
    else
    {
        game_start.setFillColor(sf::Color::White);
        game_start.setOutlineThickness(0);
    }
};
