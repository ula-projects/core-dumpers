#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Player();
    ~Player();
    void draw(sf::RenderWindow &window) const;
    void update();
};
