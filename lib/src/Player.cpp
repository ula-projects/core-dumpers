#include "Player.hpp"
#include <iostream>

Player::Player(b2World &world) : sprite(Settings::textures["player"])
{
    sprite.setTextureRect({{0, 0}, {16, 16}});
    sprite.setOrigin({Settings::TILE_SIZE / 2.f, Settings::TILE_SIZE / 2.f});

    // Configura cuerpo físico
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.f, 0.f); // Posición inicial (en píxeles)
    body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    float half = Settings::TILE_SIZE / 2.f;
    shape.SetAsBox(half, half); // Tamaño igual a un tile

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Player::update(float delta_time)
{
    float speed = 200.f;
    std::cout << coordinates.rad_angle << "     \r" << std::flush;

    coordinates.updateCoordinates(getPosition());

    b2Vec2 gravity(980.f, 970.f);
    b2Vec2 vel(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        vel.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        vel.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        vel.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        vel.x += speed;

    body->SetLinearVelocity(vel);
    body->ApplyForce(gravity, body->GetWorldCenter(), true);

    float angle = coordinates.rad_angle; // en radianes
    body->SetTransform(body->GetPosition(), angle);
    // Actualiza posición del sprite
    b2Vec2 pos = body->GetPosition();
    sprite.setPosition({pos.x, pos.y});

    sprite.setRotation(sf::Angle(sf::radians(body->GetAngle())));
    // sprite.setRotation(sf::Angle(-sf::degrees(coordinates.deg_angle - 90)));
}

sf::Vector2f Player::getPosition()
{
    return sprite.getPosition();
}