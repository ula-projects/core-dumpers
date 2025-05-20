#include <cmath>

struct XY
{
    float x;
    float y;

    XY();
    XY(float _x, float _y);

    void setCoordinates(float _x, float _y);
};

struct AABB
{
    XY center;
    float half_dimension;

    AABB();
    AABB(XY _center, float _half_size);

    void setBoundary(XY _center, float _half_dimension);
    bool isRegionInsideCircle(XY _center, float _radius);
    bool isCenterInsideCircle(XY _center, float _radius);
    bool isRegionOutsideCircle(XY _center, float _radius);
};