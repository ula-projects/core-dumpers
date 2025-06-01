#include <SFML/Graphics.hpp>
#include <vector>
#include <box2d/box2d.h>
#include <memory>

#include "Settings.hpp"
#include "Ground.hpp"

class Planet
{
private:
    std::vector<std::vector<std::shared_ptr<Ground>>> grid;
    sf::Sprite ground_sprite;
    // b2BodyDef ground_body_def;
    // b2Body *ground_body;

public:
    Planet(b2World &world);
    ~Planet();

    void generateFromImage(b2World &world);
    void draw(sf::RenderWindow &window, sf::Vector2f _position);
    void update(float _delta_time, b2World &_world, sf::Vector2f _position);

    std::vector<std::shared_ptr<Ground>> getTilesByRange(sf::Vector2f _position, unsigned int _range);
};
