#include <AABB.hpp>

XY::XY()
{
    x = 0;
    y = 0;
}

XY::XY(float _x, float _y)
{
    x = _x;
    y = _y;
}

void XY::setCoordinates(float _x, float _y)
{
    x = _x;
    y = _y;
}

AABB::AABB()
{
    half_dimension = 0;
}

AABB::AABB(XY _center, float _half_size)
{
    center = _center;
    half_dimension = _half_size;
}

void AABB::setBoundary(XY _center, float _half_dimension)
{
    center = _center;
    half_dimension = _half_dimension;
};

bool AABB::isCenterInsideCircle(XY _center, float _radius)
{
    // return std::sqrt(std::pow(std::abs(center.x), 2) + std::pow(std::abs(center.y), 2)) <= _radius;
    return std::sqrt(std::pow(std::abs(center.x - _center.y), 2) + std::pow(std::abs(center.y - _center.y), 2)) <= _radius;
}

bool AABB::isRegionInsideCircle(XY _center, float _radius)
{

    float corners[4][2] = {
        {center.x - half_dimension, center.y - half_dimension},  // Top-Left
        {center.x + half_dimension, center.y - half_dimension},  // Top-Right
        {center.x - half_dimension, center.y + half_dimension},  // Bottom-Left
        {center.x + half_dimension, center.y + half_dimension}}; // Bottom-Right

    for (auto &corner : corners)
    {
        float x = corner[0];
        float y = corner[1];

        if (std::sqrt(std::pow(x - _center.x, 2) + std::pow(y - _center.y, 2)) > _radius)
        {
            return false;
        }
    }

    return true;
}

bool AABB::isRegionOutsideCircle(XY _center, float _radius)
{
    if (isCenterInsideCircle(_center, _radius))
    {
        return false;
    }

    float cx = std::abs(center.x - _center.x) - half_dimension / 2;
    float cy = std::abs(center.y - _center.y) - half_dimension / 2;

    return std::sqrt(std::pow(cx, 2) + std::pow(cy, 2)) > _radius;
}
