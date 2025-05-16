#include <Game.hpp>

Game::Game() : camera(player.getPosition())
{
}

void Game::draw(sf::RenderWindow &window)
{
    qt.draw(window);
    window.setView(camera.getCamera());
    player.draw(window);
}

void Game::update(float &delta_time)
{
    player.update(delta_time);

    camera.setCenter(player.getPosition(), delta_time);
}
