#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <filesystem>
#include <string>
#include <vector>
#include <memory>
#include "Enums.hpp"

namespace fs = std::filesystem;
template <typename K, typename T>
using unordered_map = std::unordered_map<K, T>;
using string = std::string;
template <typename T>
using shared_ptr = std::shared_ptr<T>;

template <typename T>
using vector = std::vector<T>;

struct Settings
{
    static const fs::path ASSETS_PATH;
    static const fs::path GRAPHICS_PATH;

    static constexpr float PLAYER_SPEED{1000.0f};
    static constexpr float ENEMY_SPEED{10.0f};
    static constexpr float TILE_SIZE{16.0f};
    static constexpr unsigned int VIEW_RANGE{20};
    static constexpr float PLANET_RADIUS{256.0f};
    static constexpr float PLANET_SIZE{512.0f};
    static constexpr float WORLD_CENTER{4096.f};

    static constexpr float GRAVITY_FORCE{980.f};
    static constexpr float JUMP_FORCE{3500.f};
    static constexpr float PLAYER_VELOCITY{1500.f};
    static constexpr float SCREEN_WIDTH{1280};
    static constexpr float SCREEN_HEIGHT{720};

    static unordered_map<string, sf::Texture> textures;
    static unordered_map<string, sf::Font> fonts;

    static void init();

    static void loadTextures();
    static void loadFonts();
};