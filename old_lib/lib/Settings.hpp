#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <filesystem>
#include <string>

template <typename K, typename T>
using unordered_map = std::unordered_map<K, T>;

namespace fs = std::filesystem;

enum class ScreenSize
{
    Small,  // 540p
    Medium, // 720p
    Large   // 1080p
};
enum class PlanetRadius
{
    Small,  // 256
    Medium, // 348
    Large   // 512
};

struct Settings
{
    static const fs::path ASSETS_PATH;
    static const fs::path GRAPHICS_PATH;

    static constexpr float PLAYER_SPEED{50.0f};
    static constexpr float TYLE_SIZE{16.0f};
    static constexpr unsigned int VIEW_RANGE{20};
    static constexpr float UNIVERSE_SIZE{1024.0f};
    static constexpr float PLANET_RADIUS{256.0f};
    static constexpr float TILE_SIZE{16.0f};
    static constexpr float GRAVITY_FORCE{9.8f};
    static constexpr sf::Vector2f WORLD_CENTER{512.0f, 512.0f};

    static unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;

    static void init();

    static void loadTextures();
};

// #include <filesystem>
// #include <string>
// #include <unordered_map>

// namespace fs = std::filesystem;

// #include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>

// struct Settings
// {
//     static const fs::path ASSETS_PATH;
//     static const fs::path GRAPHICS_PATH;
//     static const fs::path SOUNDS_PATH;
//     static const fs::path FONTS_PATH;

//     static constexpr int WINDOW_WIDTH{1280};
//     static constexpr int WINDOW_HEIGHT{720};
//     static constexpr int VIRTUAL_WIDTH{512};
//     static constexpr int VIRTUAL_HEIGHT{288};
//     static constexpr float BIRD_WIDTH{39.f};
//     static constexpr float BIRD_HEIGHT{28.f};
//     static constexpr float LOG_WIDTH{70.f};
//     static constexpr float LOG_HEIGHT{288.f};
//     static constexpr float LOGS_GAP{90.f};
//     static constexpr float GROUND_HEIGHT{16.f};
//     static constexpr float BACKGROUND_LOOPING_POINT{1157.f};
//     static constexpr float MAIN_SCROLL_SPEED{100.f};
//     static constexpr float BACK_SCROLL_SPEED{50.f}; // MAIN_SCROLL_SPEED / 2
//     static constexpr float GRAVITY{980.f};
//     static constexpr float JUMP_TAKEOFF_SPEED{GRAVITY / 6.f};
//     static constexpr float TIME_TO_SPAWN_LOGS{1.5f};
//     static constexpr int MEDIUM_TEXT_SIZE{18};
//     static constexpr int HUGE_TEXT_SIZE{56};
//     static constexpr int FLAPPY_TEXT_SIZE{28};

//     static std::unordered_map<std::string, sf::Texture> textures;
//     static std::unordered_map<std::string, sf::SoundBuffer> sound_buffers;
//     static std::unordered_map<std::string, sf::Sound> sounds;
//     static std::unordered_map<std::string, sf::Font> fonts;

//     static sf::Music music;

//     static void init();

//     static void load_textures();

//     static void load_sounds();

//     static void load_fonts();
// };