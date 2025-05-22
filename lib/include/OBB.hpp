#include <AABB.hpp>
#include <vector>

struct OBB : public AABB
{
    float angle;

    OBB();
    OBB(XY _center, float _width, float _height);
    ~OBB();

    void setBoundary(XY _center, float _width, float _height, float _angle);
};
