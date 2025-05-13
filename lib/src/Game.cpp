#include <Game.hpp>

Game::Game()
{
}

void Game::draw(sf::RenderWindow &window) const
{
    window.setView(camera.getCamera());
    player.draw(window);
}

void Game::update(float &delta_time)
{
    player.update(delta_time);

    camera.setCenter(player.getPosition(), delta_time);
}