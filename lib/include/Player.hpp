#include <SFML/Graphics.hpp>
#include <cmath>

class Player
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float SPEED = 50.0f;
    bool grounded;

public:
    Player();
    ~Player();
    void draw(sf::RenderWindow &window) const;
    void update(float delta_time);
    sf::Vector2f getPosition();
};
