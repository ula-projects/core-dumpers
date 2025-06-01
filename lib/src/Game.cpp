#include "Game.hpp"

Game::Game() : world(b2Vec2(0.f, 0.f)), background(Settings::textures["background"])
{
    game_state = GameState::MainMenu;

    world.SetContactListener(&contact_listener);
    player.init(world);
    planet.init(world);

    enemies.push_back(std::make_shared<FlyingEnemy>(sf::Vector2f({4096, -40})));

    for (auto &enemy : enemies)
    {
        enemy->init(world, sf::Vector2f({4096, -40}));
    }

    background.setTextureRect({{0, 0}, {1024, 1024}});
    background.setOrigin({512, 512});

    // enemies.push_back(std::make_shared<FlyingEnemy>(sf::Vector2f({4200, -40})));
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
        camera.setCenter(player.getPosition());
        game_state = GameState::Playing;

        break;
    case GameState::Playing:
        world.Step(1.f / 60.f, 8, 3);
        player.update(delta_time);
        picaxe.update(window, planet.getTilesByRange(player.getPosition(), 1));
        camera.update(player.getPosition(), delta_time, player.getCoordinates());

        for (auto &enemy : enemies)
        {
            enemy->update(delta_time);
        }
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
        for (auto &enemy : enemies)
        {
            enemy->draw(window);
        }
        break;
    case GameState::Paused:
        break;
    default:
        break;
    }
}
