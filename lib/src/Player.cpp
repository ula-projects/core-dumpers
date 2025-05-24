#include <Player.hpp>
#include <iostream>

Player::Player() : sprite(texture)
{
    if (!texture.loadFromFile("./assets/textures/slime.png"))
    {
        // Error - considerar excepciones
    }
    sprite.setTexture(texture);
    sprite.setTextureRect({{0, 0}, {14, 15}});
    sprite.setOrigin({7, 7.5});
    // sprite.setScale({4, 4});
    sprite.setPosition({512, 400});
    grounded = false;
    jumping = false;
    free_movement = true;

    health_points = 100;
    max_health = 100;
    attack_points = 20;
    attack_range = 15;
}

Player::~Player()
{
}

sf::Vector2f Player::getPosition()
{
    return sprite.getPosition();
}

int Player::getHealthPoints() const
{
    return health_points;
}

void Player::takeDamage(int damage)
{
    health_points -= damage;

    if (health_points <= 0)
    {
        // manejar muerte
        health_points = 0;
    }
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

void Player::update(float delta_time)
{
    coordinates.updateCoordinates(sprite.getPosition());
    if (free_movement)
    {
        sf::Vector2f movement({0.0f, 0.0f});

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            sprite.setScale({-1, 1});
            movement.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            sprite.setScale({1, 1});
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
    }
    else
    {

        // Update Polar Coordinates
        // Vars - movement vectors
        sf::Vector2f movement({0.0f, 0.0f});
        sf::Vector2f gravity_movement({0, 0});
        sf::Vector2f jump_vector({0, 0});
        // Vars - rotation angle;
        sf::Angle rotation_angle = -sf::degrees(coordinates.angle - 90);
        sprite.setRotation(rotation_angle);

        if (coordinates.radius <= 50)
        {
            grounded = true;
        }
        else
        {
            grounded = false;
        }

        if (!grounded)
        {
            gravity_movement.x = (-0.5f) * std::cos(coordinates.rad_angle);
            gravity_movement.y = (0.5f) * std::sin(coordinates.rad_angle);
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                grounded = false;
                jumping = true;
                jump_timer = 0;
            }
        }

        if (jumping)
        {
            jump_timer += delta_time;

            if (jump_timer > 1.0f)
            {
                jumping = false;
            }
            jump_vector.x = 50.0f * cosf(coordinates.rad_angle);
            jump_vector.y = -50.0f * sinf(coordinates.rad_angle);
            jump_vector *= delta_time;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            sprite.setScale({-1, 1});
            movement.x = std::cos(coordinates.rad_angle + (90 * M_PI / 180));
            movement.y = -std::sin(coordinates.rad_angle + (90 * M_PI / 180));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            sprite.setScale({1, 1});
            movement.x = std::cos(coordinates.rad_angle - (90 * M_PI / 180));
            movement.y = -std::sin(coordinates.rad_angle - (90 * M_PI / 180));
        }

        sprite.move(gravity_movement + (movement * SPEED * delta_time) + jump_vector);

        // if (movement.x != 0.0f || movement.y != 0.0f)
        // {
        //     float magnitude = std::sqrt(std::pow(movement.x, 2) + std::pow(movement.y, 2));
        //     movement /= magnitude;
        // }
    }
}