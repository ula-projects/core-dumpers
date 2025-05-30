#pragma once

#include <algorithm>
#include "AABB.hpp"

struct OBB : public AABB
{
    float angle;

    OBB();
    OBB(XY _center, float _width, float _height);
    ~OBB();

    void setBoundary(XY _center, float _width, float _height, float _angle);
    vector<XY> getOBBVertex();

    bool intersectsSAT(AABB _aabb_boundary);
};

void projectOnAxis(std::vector<XY> _vertexs, XY &_axis, float &min, float &max);
bool overlapOnAxis(const std::vector<XY> &_aabb_vertexs, const std::vector<XY> &_obb_vertexs, XY &axis);