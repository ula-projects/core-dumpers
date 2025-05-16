#include <SFML/Graphics.hpp>
#include <cmath>

struct PolarCoordinates
{
    float angle;
    float rad_angle;
    float radius;
    PolarCoordinates();
    void updateCoordinates(sf::Vector2f postion);
};
