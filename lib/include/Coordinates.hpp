#include <SFML/Graphics.hpp>

struct PolarCoordinates
{
    float angle;
    float rad_angle;
    float radius;
    PolarCoordinates();
    void updateCoordinates(sf::Vector2f postion);
};
