#pragma once
#include <box2d/box2d.h>

#include "Settings.hpp"

enum class GroundType
{
    Rock,
    BeedRock,
    Core,
};

class Ground
{
private:
    GroundType type;
    sf::Vector2f position;
    b2Fixture *fixture;
    b2Body *planet_body;
    bool has_fixture;

public:
    Ground(b2Body *_planet_body, GroundType _type, float _x, float _y);
    ~Ground();

    sf::Vector2f getPosition();

    void draw(sf::RenderWindow &windor, sf::Sprite sprite);

    bool hasFixture();

    bool destroyTile(sf::Vector2f _position);
    void createFixture();
    void deleteFixture();
};
