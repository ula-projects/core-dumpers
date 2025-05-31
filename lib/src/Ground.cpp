#include "Ground.hpp"

Ground::Ground(GroundType _type, float _x, float _y)
{
    position = sf::Vector2f(_x, _y);
    type = _type;
    fixture = nullptr;
}

Ground::~Ground()
{
}

sf::Vector2f Ground::getPosition()
{
    return position;
}

bool Ground::hasFixture()
{
    return fixture;
}

void createFixture() {};
void deleteFixture() {};