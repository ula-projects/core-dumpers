#include "Ground.hpp"

Ground::Ground(b2Body *_planet_body, GroundType _type, float _x, float _y)
{
    position = sf::Vector2f(_x, _y);
    type = _type;
    planet_body = _planet_body;
    fixture = nullptr;
    has_fixture = false;
}

Ground::~Ground()
{
}

void Ground::draw(sf::RenderWindow &window, sf::Sprite sprite)
{
    switch (type)
    {
    case GroundType::Rock:
        sprite.setTextureRect({{0, 0}, {static_cast<int>(Settings::TILE_SIZE), static_cast<int>(Settings::TILE_SIZE)}});
        sprite.setPosition({position.x * Settings::TILE_SIZE, position.y * Settings::TILE_SIZE});
        break;
    case GroundType::BeedRock:
        sprite.setTextureRect({{static_cast<int>(Settings::TILE_SIZE), 0}, {static_cast<int>(Settings::TILE_SIZE), static_cast<int>(Settings::TILE_SIZE)}});
        sprite.setPosition({position.x * Settings::TILE_SIZE, position.y * Settings::TILE_SIZE});
        break;
    case GroundType::Core:
        sprite.setTextureRect({{static_cast<int>(Settings::TILE_SIZE) * 2, 0}, {static_cast<int>(Settings::TILE_SIZE), static_cast<int>(Settings::TILE_SIZE)}});
        sprite.setPosition({position.x * Settings::TILE_SIZE, position.y * Settings::TILE_SIZE});
        break;

    default:
        break;
    }
    window.draw(sprite);
}

sf::Vector2f Ground::getPosition()
{
    return position;
}

bool Ground::hasFixture()
{
    return has_fixture;
}

void Ground::createFixture()
{
    if (!has_fixture)
    {
        b2PolygonShape shape;
        float tileHalfSize = Settings::TILE_SIZE / 2.f;

        float worldX = position.x * Settings::TILE_SIZE;
        float worldY = position.y * Settings::TILE_SIZE;

        shape.SetAsBox(tileHalfSize, tileHalfSize,
                       b2Vec2(worldX + tileHalfSize, worldY + tileHalfSize), 0.f);
        b2FixtureDef fixture_def;
        fixture_def.shape = &shape;
        fixture_def.density = 1.f;
        fixture_def.friction = 1.f;
        fixture = planet_body->CreateFixture(&fixture_def);
        has_fixture = true;
    }
}

bool Ground::destroyTile(sf::Vector2f _position)
{
    sf::FloatRect destruction_zone({{position.x * Settings::TILE_SIZE, position.y * Settings::TILE_SIZE}, {Settings::TILE_SIZE, Settings::TILE_SIZE}});

    if (destruction_zone.contains(_position))
    {
        deleteFixture();
        return true;
    }
    return false;
}

void Ground::deleteFixture()
{
    if (has_fixture)
    {
        planet_body->DestroyFixture(fixture);
        has_fixture = false;
    }
}