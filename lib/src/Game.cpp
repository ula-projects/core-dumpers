#include "Game.hpp"

Game::Game() : world(gravity), player(world), planet(world), background(Settings::textures["background"])
{
    game_state = GameState::MainMenu;
    gravity = b2Vec2(0.f, 0.f);
    world.SetGravity(gravity);
    planet.generateFromImage();
    background.setTextureRect({{0, 0}, {1024, 1024}});
    background.setOrigin({512, 512});
}

Game::~Game()
{
}

void Game::update(float delta_time, sf::RenderWindow &window)
{
    switch (game_state)
    {
    case GameState::MainMenu:
        menu.mainMenuUpdate(window, game_state);
        break;
    case GameState::Loading:
        game_state = GameState::Playing;
        break;
    case GameState::Playing:
        world.Step(1.f / 60.f, 8, 3);
        camera.update(player.getPosition(), delta_time);
        player.update(delta_time);
        break;
    case GameState::Paused:
        break;
    default:
        break;
    }
}

void Game::draw(sf::RenderWindow &window)
{
    switch (game_state)
    {
    case GameState::MainMenu:

        background.setPosition({Settings::SCREEN_WIDTH / 2, Settings::SCREEN_HEIGHT / 2});
        background.setScale({1.25f, 1.25f});
        window.draw(background);
        menu.mainMenuDraw(window);
        break;
    case GameState::Loading:
        background.setPosition({Settings::SCREEN_WIDTH / 2, Settings::SCREEN_HEIGHT / 2});
        background.setScale({1.25f, 1.25f});
        window.draw(background);
        break;
    case GameState::Playing:
        window.setView(camera.getCamera());
        background.setPosition({512, 512});
        background.setScale({1.f, 1.f});
        window.draw(background);
        planet.draw(window, player.getPosition());
        player.draw(window);
        break;
    case GameState::Paused:
        break;
    default:
        break;
    }
}

// GameState Game::getGameState()
// {
//     return game_state;
// }

// void Game::setGameState(GameState _state)
// {
//     game_state = _state;
// }