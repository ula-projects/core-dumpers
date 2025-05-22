#include <Coordinates.hpp>

PolarCoordinates::PolarCoordinates()
{
    angle = 0;
    radius = 0;
}

void PolarCoordinates::updateCoordinates(sf::Vector2f position)
{
    float pos_x = position.x;
    float pos_y = -position.y;

    // radius = std::abs(std::sqrt(std::pow(pos_x, 2) + std::pow(pos_y, 2)) - std::sqrt(std::pow(512, 2) + std::pow(512, 2)));
    radius = std::abs(std::sqrt(std::pow(pos_x - 512, 2) + std::pow(pos_y + 512, 2)));

    rad_angle = std::atan2(pos_y + 512, pos_x - 512);
    angle = rad_angle * 180 / M_PI;

    if (angle < 0)
    {
        angle += 360;
    }
    rad_angle = angle * M_PI / 180;
};
