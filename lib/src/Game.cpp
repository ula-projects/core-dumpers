#include <Game.hpp>
#include <iostream>

Game::Game() : camera(player.getPosition())
{
    world_center.setCoordinates(512, 512);
    world_boundary.setBoundary(world_center, 512);

    qt.setBoundary(world_boundary);
    qt.generateWorld();

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
        qt.draw(window);
        window.setView(camera.getCamera());
        player.draw(window);
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
        player.update(delta_time);
        camera.setCenter(player.getPosition(), delta_time);
    }
}
