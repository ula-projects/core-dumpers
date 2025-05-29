#include "OBB.hpp"

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

vector<XY> OBB::getOBBVertex()
{
    vector<XY> vertex = AABB::getAABBVertex();

    std::transform(vertex.begin(), vertex.end(), vertex.begin(), [&](XY _vertex)
                   { return _vertex.rotatedVector(this->center, this->angle); });

    return vertex;
}

bool OBB::intersectsSAT(AABB _aabb_boundary)
{
    vector<XY> verts_aabb = _aabb_boundary.getAABBVertex();
    vector<XY> verts_obb = getOBBVertex();

    // proyecciones de los vectores unitarios de cada eje.
    std::vector<XY> axes = {
        XY(1, 0), // eje X del AABB
        XY(0, 1), // eje Y del AABB
        XY(verts_obb[1].x - verts_obb[0].x, verts_obb[1].y - verts_obb[0].y).normalizedVector(),
        XY(verts_obb[2].x - verts_obb[1].x, verts_obb[2].y - verts_obb[1].y).normalizedVector()};

    for (auto axis : axes)
    {
        if (!overlapOnAxis(verts_aabb, verts_obb, axis))
        {
            return false;
        }
    }
    return true;
};

void projectOnAxis(std::vector<XY> _vertexs, XY &_axis, float &min, float &max)
{
    min = max = _vertexs[0].dotProduct(_axis);
    for (auto vertex : _vertexs)
    {
        float projection = vertex.dotProduct(_axis);
        if (projection < min)
            min = projection;
        if (projection > max)
            max = projection;
    }
}

bool overlapOnAxis(const std::vector<XY> &_aabb_vertexs, const std::vector<XY> &_obb_vertexs, XY &axis)
{
    float minA, maxA, minB, maxB;
    projectOnAxis(_aabb_vertexs, axis, minA, maxA);
    projectOnAxis(_obb_vertexs, axis, minB, maxB);
    return !(maxA < minB || maxB < minA);
}