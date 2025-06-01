#include <Settings.hpp>
#include <stdexcept>

const fs::path Settings::ASSETS_PATH{"assets"};

const fs::path Settings::GRAPHICS_PATH{Settings::ASSETS_PATH / "textures"};

unordered_map<std::string, std::shared_ptr<sf::Texture>> Settings::textures{};

void Settings::init()
{
    Settings::loadTextures();
}

void Settings::loadTextures()

{
    auto playerTex = std::make_shared<sf::Texture>();
    if (!playerTex->loadFromFile(Settings::GRAPHICS_PATH / "player-16.png"))
    {
        throw std::runtime_error{"Error loading player's texture"};
    }
    Settings::textures["player"] = playerTex;

    auto bgTex = std::make_shared<sf::Texture>();
    if (!bgTex->loadFromFile(Settings::GRAPHICS_PATH / "nebula-1.png"))
    {
        throw std::runtime_error{"Error loading background texture"};
    }
    Settings::textures["background"] = bgTex;

    auto groundTex = std::make_shared<sf::Texture>();
    if (!groundTex->loadFromFile(Settings::GRAPHICS_PATH / "world_tileset.png"))
    {
        throw std::runtime_error{"Error loading ground texture"};
    }
    Settings::textures["ground"] = groundTex;
    // sf::Texture texture{};

    // if (!texture.loadFromFile(Settings::GRAPHICS_PATH / "player-16.png"))
    // {
    //     throw std::runtime_error{"Error loading player's texture"};
    // }

    // Settings::textures["player"] = texture;

    // if (!texture.loadFromFile(Settings::GRAPHICS_PATH / "nebula-1.png"))
    // {
    //     throw std::runtime_error{"Error loading background's texture"};
    // }

    // Settings::textures["background"] = texture;

    // if (!texture.loadFromFile(Settings::GRAPHICS_PATH / "nebula-1.png"))
    // {
    //     throw std::runtime_error{"Error loading background's texture"};
    // }

    // Settings::textures["background"] = texture;

    // if (!texture.loadFromFile(Settings::GRAPHICS_PATH / "world_tileset.png"))
    // {
    //     throw std::runtime_error{"Error loading ground's textures"};
    // }

    // Settings::textures["ground"] = texture;
}

// const fs::path Settings::SOUNDS_PATH{Settings::ASSETS_PATH / "sounds"};

// const fs::path Settings::FONTS_PATH{Settings::ASSETS_PATH / "fonts"};

// std::unordered_map<std::string, sf::Texture> Settings::textures{};

// std::unordered_map<std::string, sf::SoundBuffer> Settings::sound_buffers;

// std::unordered_map<std::string, sf::Sound> Settings::sounds{};

// std::unordered_map<std::string, sf::Font> Settings::fonts{};

// sf::Music Settings::music{};

// void Settings::init()
// {
//     Settings::load_textures();
//     Settings::load_sounds();
//     Settings::load_fonts();
// }

// void Settings::load_textures()
// {
//     sf::Texture texture{};

//     if (!texture.loadFromFile(Settings::GRAPHICS_PATH / "bird.png"))
//     {
//         throw std::runtime_error{"Error loading texture graphics/bird.png"};
//     }

//     Settings::textures["bird"] = texture;

//     if (!texture.loadFromFile(Settings::GRAPHICS_PATH / "background.png"))
//     {
//         throw std::runtime_error{"Error loading texture graphics/background.png"};
//     }

//     Settings::textures["background"] = texture;

//     if (!texture.loadFromFile(Settings::GRAPHICS_PATH / "ground.png"))
//     {
//         throw std::runtime_error{"Error loading texture graphics/ground.png"};
//     }

//     Settings::textures["ground"] = texture;

//     if (!texture.loadFromFile(Settings::GRAPHICS_PATH / "log.png"))
//     {
//         throw std::runtime_error{"Error loading texture graphics/log.png"};
//     }

//     Settings::textures["Log"] = texture;
// }

// void Settings::load_sounds()
// {
//     sf::SoundBuffer buffer;
//     sf::Sound sound;

//     if (!buffer.loadFromFile(Settings::SOUNDS_PATH / "jump.wav"))
//     {
//         throw std::runtime_error{"Error loading sound sounds/jump.wav"};
//     }

//     auto result = Settings::sound_buffers.emplace("jump", buffer);

//     sound.setBuffer(result.first->second);
//     Settings::sounds["jump"] = sound;

//     if (!buffer.loadFromFile(Settings::SOUNDS_PATH / "explosion.wav"))
//     {
//         throw std::runtime_error{"Error loading sound sounds/explosion.wav"};
//     }

//     result = Settings::sound_buffers.emplace("explosion", buffer);

//     sound.setBuffer(result.first->second);
//     Settings::sounds["explosion"] = sound;

//     if (!buffer.loadFromFile(Settings::SOUNDS_PATH / "hurt.wav"))
//     {
//         throw std::runtime_error{"Error loading sound sounds/hurt.wav"};
//     }

//     result = Settings::sound_buffers.emplace("hurt", buffer);

//     sound.setBuffer(result.first->second);
//     Settings::sounds["hurt"] = sound;

//     if (!buffer.loadFromFile(Settings::SOUNDS_PATH / "score.wav"))
//     {
//         throw std::runtime_error{"Error loading sound sounds/score.wav"};
//     }

//     result = Settings::sound_buffers.emplace("score", buffer);

//     sound.setBuffer(result.first->second);
//     Settings::sounds["score"] = sound;

//     if (!Settings::music.openFromFile(Settings::SOUNDS_PATH / "marios_way.ogg"))
//     {
//         throw std::runtime_error{"Error loading music sounds/marios_way.ogg"};
//     }
// }

// void Settings::load_fonts()
// {
//     sf::Font font;

//     if (!font.loadFromFile(Settings::FONTS_PATH / "font.ttf"))
//     {
//         throw std::runtime_error{"Error loading font fonts/font.ttf"};
//     }

//     Settings::fonts["font"] = font;

//     if (!font.loadFromFile(Settings::FONTS_PATH / "flappy.ttf"))
//     {
//         throw std::runtime_error{"Error loading font fonts/flappy.ttf"};
//     }

//     Settings::fonts["flappy"] = font;
// }