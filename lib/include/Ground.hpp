#include <box2d/box2d.h>

#include "Settings.hpp"

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
    sf::Vector2f position;

public:
    b2Fixture *fixture;
    Ground(GroundType _type, float _x, float _y);
    ~Ground();

    sf::Vector2f getPosition();

    bool hasFixture();

    void createFixture();
    void deleteFixture();
};
