#include <Game.hpp>

Game::Game()
{
}

void Game::draw(sf::RenderWindow &window) const
{
    qt.draw(window);
    window.setView(camera.getCamera());
    sf::RectangleShape aasas({200, 200});
    aasas.setPosition({220, 220});
    aasas.setFillColor(sf::Color::Red);
    window.draw(aasas);
    player.draw(window);
}

void Game::update(float &delta_time)
{
    player.update(delta_time);

    camera.setCenter(player.getPosition(), delta_time);
}