#include <stdexcept>
#include "Settings.hpp"

const fs::path Settings::ASSETS_PATH{"assets"};

const fs::path Settings::GRAPHICS_PATH{Settings::ASSETS_PATH / "textures"};

unordered_map<string, sf::Texture> Settings::textures{};
unordered_map<string, sf::Font> Settings::fonts{};

void Settings::init()
{
    loadTextures();
    loadFonts();
}

void Settings::loadTextures()
{
    sf::Texture player_texture{};

    if (!player_texture.loadFromFile(Settings::GRAPHICS_PATH / "player.png"))
    {
        throw std::runtime_error{"Error loading player's texture"};
    }

    Settings::textures["player"] = player_texture;

    sf::Texture ground_texture{};

    if (!ground_texture.loadFromFile(Settings::GRAPHICS_PATH / "ground.png"))
    {
        throw std::runtime_error{"Error loading ground texture"};
    }

    Settings::textures["ground"] = ground_texture;

    sf::Texture background_texture{};

    if (!background_texture.loadFromFile(Settings::GRAPHICS_PATH / "background.png"))
    {
        throw std::runtime_error{"Error loading background texture"};
    }

    Settings::textures["background"] = background_texture;
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