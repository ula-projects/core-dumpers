#include <Player.hpp>

Player::Player() : sprite(texture)
{
    if (!texture.loadFromFile("./assets/textures/player-16.png"))
    {
        // Error - considerar excepciones
    }
    sprite.setTexture(texture);
    sprite.setTextureRect({{0, 0}, {16, 16}});
    sprite.setOrigin({8, 8});
    sprite.setPosition({512, 200});
    grounded = false;
    jumping = false;
    sprite_time = 0;
    free_movement = false;
    player_boundary.setBoundary(XY(getPosition().x, getPosition().y), 8, 8, coordinates.rad_angle);
}

Player::~Player()
{
}

sf::Vector2f Player::getPosition()
{
    return sprite.getPosition();
}

void Player::draw(sf::RenderWindow &window) const
{
    sf::RectangleShape box_col({16, 16});
    box_col.setOrigin({8, 8});
    sf::Angle rotation_angle = -sf::degrees(coordinates.angle - 90);
    box_col.setPosition(sprite.getPosition());
    box_col.setRotation(rotation_angle);
    box_col.setFillColor(sf::Color::Transparent);
    box_col.setOutlineColor(sf::Color::Red);
    box_col.setOutlineThickness(1);

    rotation_angle = -sf::degrees(coordinates.angle - 90);
    box_col.setRotation(rotation_angle);
    window.draw(box_col);
    window.draw(sprite);
}

void Player::update(float delta_time, vector<shared_ptr<QuadTreeNode>> collision_list)
{
    coordinates.updateCoordinates(sprite.getPosition());
    sprite_time += delta_time;

    if (sprite_time >= 0.125f)
    {
        sprite_time = 0;
        current_sprite = current_sprite + 1 >= 4 ? 0 : current_sprite += 1;
        sprite.setTextureRect({{current_sprite * 16, 0}, {16, 16}});
    }

    player_boundary.setBoundary(XY(getPosition().x, getPosition().y), 8, 8, coordinates.rad_angle);

    grounded = false;

    for (auto ground : collision_list)
    {
        if (!ground->getIsEmpty())
        {
            if (player_boundary.intersectsSAT(ground->getBoundary()))
            {
                grounded = true;
            }
        }
    }

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

        if (!grounded)
        {
            gravity_movement.x = (-0.5f) * std::cos(coordinates.rad_angle);
            gravity_movement.y = (0.5f) * std::sin(coordinates.rad_angle);

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

        sprite.move(gravity_movement + (movement * SPEED * delta_time) + jump_vector);
    }
}
