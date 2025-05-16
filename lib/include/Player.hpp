#include <SFML/Graphics.hpp>
#include <cmath>
#include <Coordinates.hpp>

class Player
{
private:
    PolarCoordinates coordinates;
    sf::Texture texture;
    sf::Sprite sprite;

    float SPEED = 50.0f;

    bool jumping;
    float jump_timer;
    bool grounded;

public:
    Player();
    ~Player();
    sf::Vector2f getPosition();
    void draw(sf::RenderWindow &window) const;
    void update(float delta_time);
};
