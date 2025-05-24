#include <Game.hpp>
#include <iostream>

Game::Game() : camera(), ground(ground_texture)
{
    player = std::make_shared<Player>();
    world_center.setCoordinates(512, 512);
    world_boundary.setBoundary(world_center, 512);

    qt.setBoundary(world_boundary);
    qt.generateWorld();

    if (!ground_texture.loadFromFile("./assets/textures/world_tileset.png"))
    {
    }

    ground.setTextureRect({{0, 16}, {16, 16}});
    ground.setOrigin({8, 8});
    ground.setScale({0.5f, 0.5f});

    ground_ptr = std::make_shared<sf::Sprite>(ground);

    if (!enemy_texture.loadFromFile("./assets/textures/enemy.png"))
    {
    }

    //Creacion de Enemigos
    enemies.push_back(std::make_shared<FlyingEnemy>(sf::Vector2f({200, 200}), enemy_texture));
    enemies.push_back(std::make_shared<FlyingEnemy>(sf::Vector2f({800, 800}), enemy_texture));

    game_state = 0;
}

void Game::draw(sf::RenderWindow &window)
{

    if (game_state == 0)
    {
        menu.mainMenuDraw(window);
    }
    else if (game_state == 1)
    {
        qt.draw(window, ground_ptr);
        window.setView(camera.getCamera());
        player->draw(window);
        for(auto& enemy : enemies)
        {
            enemy->draw(window);
        }
    }
}

void Game::update(float &delta_time, sf::RenderWindow &window)
{
    // mouse_position = sf::Mouse::getPosition(window);

    // Menu Principal
    if (game_state == 0)
    {
        menu.mainMenuUpdate(window, game_state);
    }
    // Juego
    else if (game_state == 1)
    {
        InteractionManager(enemies, player);
        player->update(delta_time);
        for (auto& enemy : enemies)
        {
            enemy->update(delta_time);
        }
        camera.setCenter(player->getPosition(), delta_time);
    }
}
