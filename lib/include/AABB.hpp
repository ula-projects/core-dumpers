#pragma once
#include <cmath>
#include <vector>

template <typename T>
using vector = std::vector<T>;

struct XY
{
    float x;
    float y;

    XY();
    XY(float _x, float _y);

    float docProduct(XY _axis);

    void setCoordinates(float _x, float _y);

    XY normalizedVector();
};

struct AABB
{
    XY center;
    float half_width;
    float half_height;
    // float half_dimension;

    AABB();
    AABB(XY _center, float _width, float _height);

    void setBoundary(XY _center, float _width, float _height);

    bool isRegionInsideCircle(XY _center, float _radius);
    bool isCenterInsideCircle(XY _center, float _radius);
    bool isRegionOutsideCircle(XY _center, float _radius);

    float minX() const;
    float maxX() const;
    float minY() const;
    float maxY() const;
    bool intersectsAABB(AABB _boundary);
    vector<XY> getAABBvertex();
};