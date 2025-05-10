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
    sprite.setPosition({100, 100});
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

void Player::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        sprite.setScale({-4, 4});
        sprite.move({-0.1, 0});
        // std::cout << "izquierda" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        sprite.setScale({4, 4});
        sprite.move({0.1, 0});
        // std::cout << "derecha" << std::endl;
    }
}