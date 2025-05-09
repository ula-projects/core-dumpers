#include <Game.hpp>
#include <iostream>

Game::Game() noexcept {}

void Game::draw(sf::RenderWindow &window) const
{
    std::cout << "game draw" << "\r" << std::flush;
    qt.draw(window);
}