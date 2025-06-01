#include "Player.hpp"

Player::Player() : sprite(Settings::textures["player"])
{
    sprite.setTextureRect({{0, 0}, {16, 16}});
    sprite.setOrigin({Settings::TILE_SIZE / 2.f, Settings::TILE_SIZE / 2.f});
    is_grounded = false;
    is_jumping = true;
    free_movement = false;
    current_sprite = 0;
    sprite_time = 0;

    health_points = 100;
    max_health = 100;
    attack_points = 20;
    attack_range = 15;
}

Player::~Player()
{
}

void Player::init(b2World &world)
{

    // Configura Body para el box2d
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    body_def.position.Set(4096.f, -16.f);
    // body_def.position.Set(8220.f, 4096.f);
    // body_def.position.Set(4096.f, 8220.f);
    player_b2_body = world.CreateBody(&body_def);

    // Configurando la forma
    float half = Settings::TILE_SIZE / 2.f;
    b2PolygonShape box_collider;
    box_collider.SetAsBox(half, half);

    // Configurando el fixture
    b2FixtureDef fixture_def;
    fixture_def.shape = &box_collider;
    fixture_def.density = 0.01f;
    fixture_def.friction = 1.f;
    fixture_def.restitution = 0.f;
    player_b2_body->CreateFixture(&fixture_def);

    player_b2_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    b2Vec2 pos = player_b2_body->GetPosition();
    sprite.setPosition({pos.x, pos.y});
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Player::update(float delta_time)
{
    if (is_grounded)
    {
        is_jumping = false;
    }

    coordinates.updateCoordinates(getPosition());

    // actualizar sprite rect
    sprite_time += delta_time;
    if (sprite_time >= 0.125f)
    {
        sprite_time = 0;
        current_sprite = current_sprite + 1 >= 4 ? 0 : ++current_sprite;
        sprite.setTextureRect({{current_sprite * 16, 0}, {16, 16}});
    }

    // Movimientos del jugador
    // Salto
    if (is_grounded)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            is_jumping = true;
            is_grounded = false;
            float jump_x = Settings::JUMP_FORCE * cosf(coordinates.rad_angle);
            float jump_y = -Settings::JUMP_FORCE * sinf(coordinates.rad_angle);
            b2Vec2 jump(jump_x, jump_y);

            player_b2_body->ApplyLinearImpulse(jump, player_b2_body->GetWorldCenter(), true);
        }
    }

    if (is_jumping)
    {
        float rotation_angle = -(coordinates.deg_angle - 90) * M_PI / 180;
        player_b2_body->SetTransform(player_b2_body->GetPosition(), rotation_angle);

        // mov derecha
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            sprite.setScale({1, 1});
            float angle = coordinates.rad_angle - (90 * M_PI / 180);
            float move_x = Settings::PLAYER_SPEED * std::cos(angle);
            float move_y = -Settings::PLAYER_SPEED * std::sin(angle);
            b2Vec2 movemet(move_x, move_y);

            player_b2_body->ApplyForce(movemet, player_b2_body->GetWorldCenter(), true);
        }

        // mov izquierda
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            sprite.setScale({-1, 1});
            float angle = coordinates.rad_angle + (90 * M_PI / 180);
            float move_x = Settings::PLAYER_SPEED * std::cos(angle);
            float move_y = -Settings::PLAYER_SPEED * std::sin(angle);
            b2Vec2 movemet(move_x, move_y);

            player_b2_body->ApplyForce(movemet, player_b2_body->GetWorldCenter(), true);
        }
    }

    // gravity
    float gravity_x = -Settings::GRAVITY_FORCE * cosf(coordinates.rad_angle);
    float gravity_y = Settings::GRAVITY_FORCE * sinf(coordinates.rad_angle);

    b2Vec2 gravity(gravity_x, gravity_y);
    player_b2_body->ApplyForce(gravity, player_b2_body->GetWorldCenter(), true);

    // Actualizar sprite position y rotation
    b2Vec2 pos = player_b2_body->GetPosition();
    sprite.setPosition({pos.x, pos.y});
    sprite.setRotation(sf::Angle(sf::radians(player_b2_body->GetAngle())));
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

void Player::setIsGrounded(bool _grounded)
{
    is_grounded = _grounded;
};

PolarCoordinates Player::getCoordinates()
{
    return coordinates;
};