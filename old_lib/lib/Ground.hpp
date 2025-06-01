#include <SFML/Graphics.hpp>
#include <memory>
#include <box2d/box2d.h>

enum class GroundType
{
    Rock,
    BeedRock,
    Core,
};

class Ground
{
private:
    GroundType type;

public:
    Ground(GroundType _type, float _x, float _y);
    ~Ground();
    float x;
    float y;

    bool hasFixture;
    b2Fixture *fixture;

    void createFixture();
    void deleteFixture();
};
