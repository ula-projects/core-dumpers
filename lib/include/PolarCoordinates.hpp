#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Settings.hpp"

struct PolarCoordinates
{
    float radius;
    float deg_angle;
    float rad_angle;

    PolarCoordinates();

    void updateCoordinates(sf::Vector2f position);
    float getRadAngleByPos(sf::Vector2f position, sf::Vector2f center);
};
