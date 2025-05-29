#include "AABB.hpp"

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

float XY::dotProduct(XY _axis)
{
    return x * _axis.x + y * _axis.y;
}

void XY::setCoordinates(float _x, float _y)
{
    x = _x;
    y = _y;
}

XY XY::normalizedVector()
{
    float h = std::sqrt(x * x + y * y);
    return h > 0 ? XY(x / h, y / h) : XY(0, 0);
}

XY XY::rotatedVector(XY _center, float _angle)
{
    float dx = x - _center.x;
    float dy = y - _center.y;

    return XY(
        dx * std::cos(_angle) - dy * std::sin(_angle) + _center.x,
        dx * std::sin(_angle) + dy * std::cos(_angle) + _center.y);
}

AABB::AABB()
{
    half_width = half_height = 0;
}

AABB::AABB(XY _center, float _width, float _height)
{
    center = _center;
    half_width = _width;
    half_height = _height;
}

void AABB::setBoundary(XY _center, float _width, float _height)
{
    center = _center;
    half_width = _width;
    half_height = _height;
};

bool AABB::isCenterInsideCircle(XY _center, float _radius)
{
    return std::sqrt((center.x - _center.x) * (center.x - _center.x) + (center.y - _center.y) * (center.y - _center.y)) <= _radius;
}

bool AABB::isRegionInsideCircle(XY _center, float _radius)
{
    float corners[4][2] = {
        {center.x - half_width, center.y - half_height},  // Top-Left
        {center.x + half_width, center.y - half_height},  // Top-Right
        {center.x - half_width, center.y + half_height},  // Bottom-Left
        {center.x + half_width, center.y + half_height}}; // Bottom-Right

    for (auto &corner : corners)
    {
        float x = corner[0];
        float y = corner[1];

        if ((x - _center.x) * (x - _center.x) + (y - _center.y) * (y - _center.y) > _radius * _radius)
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

    float cx = std::abs(center.x - _center.x) - half_width / 2;
    float cy = std::abs(center.y - _center.y) - half_height / 2;

    return (cx * cx + cy * cy) > (_radius * _radius);
}

float AABB::minX() const { return center.x - half_width; }
float AABB::maxX() const { return center.x + half_width; }
float AABB::minY() const { return center.y - half_height; }
float AABB::maxY() const { return center.y + half_height; }

bool AABB::intersectsAABB(AABB _boundary)
{
    return (minX() < _boundary.maxX() &&
            maxX() > _boundary.minX() &&
            minY() < _boundary.maxY() &&
            maxY() > _boundary.minY());
}

vector<XY> AABB::getAABBVertex()
{
    vector<XY> vertex;

    vertex.push_back(XY(minX(), minY()));
    vertex.push_back(XY(minX(), maxY()));
    vertex.push_back(XY(maxX(), minY()));
    vertex.push_back(XY(maxX(), maxY()));

    return vertex;
}

bool AABB::containsXY(XY _point)
{
    return _point.x >= minX() && _point.x <= maxX() && _point.y >= minY() && _point.y <= maxY();
}
