#include <OBB.hpp>

XY rotate(const XY &p, float angleRad)
{
    return XY(
        p.x * std::cos(angleRad) - p.y * std::sin(angleRad),
        p.x * std::sin(angleRad) + p.y * std::cos(angleRad));
}

std::vector<XY> getAABBVertices(const AABB &box)
{
    std::vector<XY> vertices;
    float x = box.center.x;
    float y = box.center.y;
    float hw = box.half_width;
    float hh = box.half_height;

    vertices.emplace_back(x - hw, y - hh); // Top-left
    vertices.emplace_back(x + hw, y - hh); // Top-right
    vertices.emplace_back(x + hw, y + hh); // Bottom-right
    vertices.emplace_back(x - hw, y + hh); // Bottom-left

    return vertices;
}

OBB::OBB() : AABB()
{
    angle = 0;
}

OBB::OBB(XY _center, float _width, float _height) : AABB(_center, _width, _height)
{
}

OBB::~OBB()
{
}

void OBB::setBoundary(XY _center, float _width, float _height, float _angle)
{
    AABB::setBoundary(_center, _width, _height);
    angle = _angle;
}