#include "PolarCoordinates.hpp"

PolarCoordinates::PolarCoordinates()
{
    rad_angle = deg_angle = radius = 0;
}

void PolarCoordinates::updateCoordinates(sf::Vector2f position)
{
    float pos_x = position.x - Settings::WORLD_CENTER;
    float pos_y = -position.y + Settings::WORLD_CENTER;

    radius = std::abs(std::sqrt((pos_x * pos_x) + (pos_y * pos_y)));

    rad_angle = std::atan2(pos_y, pos_x);
    deg_angle = rad_angle * 180 / M_PI;

    if (deg_angle < 0)
    {
        deg_angle += 360;
    }
    rad_angle = deg_angle * M_PI / 180;
};

float PolarCoordinates::getRadAngleByPos(sf::Vector2f position, sf::Vector2f center)
{
    float pos_x = position.x - center.x;
    float pos_y = -position.y + center.y;

    return std::atan2(pos_y, pos_x);
}
