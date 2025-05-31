#include "Settings.hpp"
#include <box2d/box2d.h>
#include "PolarCoordinates.hpp"

class Player
{
private:
    PolarCoordinates coordinates;

    sf::Sprite sprite;

    b2Body *body;

public:
    Player(b2World &world);
    ~Player();

    void update(float delta_time);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition();
};
