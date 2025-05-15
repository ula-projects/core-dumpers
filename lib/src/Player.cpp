#include <Player.hpp>

Player::Player() : sprite(texture)
{
    if (!texture.loadFromFile("./assets/textures/slime.png"))
    {
        // Error - considerar excepciones
    }
    sprite.setTexture(texture);
    sprite.setTextureRect({{0, 0}, {14, 15}});
    sprite.setOrigin({7, 7.5});
    sprite.setScale({4, 4});
    sprite.setPosition({0, -320});
    grounded = false;
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
    sf::Vector2f movement({0.0f, 0.0f});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        sprite.setScale({-4, 4});
        movement.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        sprite.setScale({4, 4});
        movement.x += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        movement.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        movement.y += 1.0f;
    }

    if (movement.x != 0.0f || movement.y != 0.0f)
    {
        float magnitude = std::sqrt(std::pow(movement.x, 2) + std::pow(movement.y, 2));
        movement /= magnitude;
    }

    sprite.move(movement * SPEED * delta_time);
    // std::cout << "Movement x: " << movement.x << " y: " << movement.y << "                   \r" << std::flush;
}

sf::Vector2f Player::getPosition()
{
    return sprite.getPosition();
}