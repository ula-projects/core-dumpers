#include <stdexcept>
#include "Settings.hpp"

// const fs::path Settings::ASSETS_PATH{"assets"};

// const fs::path Settings::GRAPHICS_PATH{Settings::ASSETS_PATH / "textures"};

unordered_map<string, sf::Texture> Settings::textures{};
unordered_map<string, sf::Font> Settings::fonts{};

void Settings::init()
{
    try
    {
        loadTextures();
        loadFonts();
    }
    catch (const std::exception &e)
    {
    }
}

void Settings::loadTextures()
{
    sf::Texture player_texture{};

    if (!player_texture.loadFromFile("./assets/textures/player.png"))
    {
        throw std::runtime_error{"Error loading player's texture"};
    }

    Settings::textures["player"] = player_texture;

    sf::Texture ground_texture{};

    if (!ground_texture.loadFromFile("./assets/textures/ground.png"))
    {
        throw std::runtime_error{"Error loading ground texture"};
    }

    Settings::textures["ground"] = ground_texture;

    sf::Texture background_texture{};

    if (!background_texture.loadFromFile("./assets/textures/background.png"))
    {
        throw std::runtime_error{"Error loading background texture"};
    }

    Settings::textures["background"] = background_texture;

    sf::Texture enemy_texture{};

    if (!enemy_texture.loadFromFile("./assets/textures/enemy.png"))
    {
        throw std::runtime_error{"Error loading enemy texture"};
    }

    Settings::textures["enemy"] = enemy_texture;
}

void Settings::loadFonts()
{
    sf::Font font;

    if (!font.openFromFile("./assets/fonts/PixelOperator8.ttf"))
    {
        throw std::runtime_error{"Error loading font family"};
    }

    Settings::fonts["pixel"] = font;
}