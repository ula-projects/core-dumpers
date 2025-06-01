#include <Game.hpp>
#include <iostream>

// : planet(world), gravity(0.f, 9.8f), world(gravity), camera(player.getPosition())
Game::Game() : world(gravity), planet(world)
{
    try
    {
        // game_settings.init();
        planet.generateFromImage(world);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Game::draw(sf::RenderWindow &window)
{
    // window.setView(camera.getCamera());
    // planet.draw(window, player.getPosition());
    // player.draw(window);
}

void Game::update(float &delta_time, sf::RenderWindow &window)
{

    // player.update(delta_time);

    // planet.update(delta_time, world, player.getPosition());

    // collision_list = {};
    // player.update(delta_time, collision_list, window);
    // camera.setCenter(player.getPosition(), delta_time);
}

// Constructor

// try
// {
// }
// catch (const std::exception &e)
// {
//     std::cerr << e.what() << '\n';
// }

// world_center.setCoordinates(512, 512);
// world_boundary.setBoundary(world_center, 512, 512);

// qt.setBoundary(world_boundary);
// qt.generateWorld();

// if (!ground_texture.loadFromFile("./assets/textures/world_tileset.png"))
// {
// }
// ground.setTextureRect({{0, 16}, {16, 16}});
// ground.setOrigin({8, 8});
// ground_ptr = std::make_shared<sf::Sprite>(ground);
// if (!background_texture.loadFromFile("./assets/textures/nebula-3.png"))
// {
// }
// background.setTextureRect({{0, 0}, {1024, 1024}});

// view_boundary.setBoundary(XY(camera.getCenter().x, camera.getCenter().y), 160, 90);

// collision_boundary.setBoundary(XY(player.getPosition().x, player.getPosition().y), 16, 16);

// game_state = 0;

// update

// switch (game_state)
// {
// case GameState::MainMenu:
//     break;
// case GameState::Playing:
//     planet.update(delta_time, world, player.getPosition());
//     break;
// case GameState::Paused:
//     break;
// case GameState::GameOver:
//     break;
// case GameState::Exiting:
//     break;
// default:
//     break;
// }

// view_boundary.setBoundary(XY(camera.getCenter().x, camera.getCenter().y), view_boundary.half_width, view_boundary.half_height);
// collision_boundary.setBoundary(XY(player.getPosition().x, player.getPosition().y), collision_boundary.half_width, collision_boundary.half_height);

// // Menu Principal
// if (game_state == 0)
// {
//     menu.mainMenuUpdate(window, game_state);
// }
// // Juego
// else if (game_state == 1)
// {
//     ground_list = qt.queryRange(view_boundary);
// collision_list = qt.queryRange(collision_boundary);
// }

// draw

//{ switch (game_state)
// {
// case GameState::MainMenu:
//     break;
// case GameState::Playing:
//     break;
// case GameState::Paused:
//     break;
// case GameState::GameOver:
//     break;
// case GameState::Exiting:
//     break;

// default:
//     break;
// }

// if (game_state == 0)

// {
//     menu.mainMenuDraw(window);
// }
// else if (game_state == 1)
// {
//     window.draw(background);
//     for (auto ground : ground_list)
//     {
//         ground->draw(window, ground_ptr);
//     }
// }}