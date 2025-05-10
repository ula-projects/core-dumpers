#include <Game.hpp>

Game::Game() {}

void Game::draw(sf::RenderWindow &window) const
{
    player.draw(window);
}

void Game::update(float &delta_time)
{
    player.update();
}