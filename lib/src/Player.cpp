#include <Player.hpp>
#include <iostream>

Player::Player() : sprite(texture)
{
    if (!texture.loadFromFile("./assets/textures/slime.png"))
    {
        // Error - manejalo
    }
    sprite.setTexture(texture);
    sprite.setTextureRect({{0, 0}, {14, 15}});
    sprite.setOrigin({7, 7.5});
    sprite.setScale({4, 4});
    sprite.setPosition({320, 320});
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

void Player::update(float delta_time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        sprite.setScale({-4, 4});
        sprite.move({-1, 0});
        // std::cout << "izquierda" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        sprite.setScale({4, 4});
        sprite.move({1, 0});
        // std::cout << "derecha" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        // sprite.setScale({-4, 4});
        sprite.move({0, -1});
        // std::cout << "izquierda" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        // sprite.setScale({4, 4});
        sprite.move({0, 1});
        // std::cout << "derecha" << std::endl;
    }
}

sf::Vector2f Player::getPosition()
{
    return sprite.getPosition();
}