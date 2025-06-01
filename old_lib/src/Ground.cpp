#include "Ground.hpp"

Ground::Ground(GroundType _type, float _x, float _y)
{
    x = _x;
    y = _y;
    type = _type;
    hasFixture = false;
    fixture = nullptr;
}

Ground::~Ground()
{
}
