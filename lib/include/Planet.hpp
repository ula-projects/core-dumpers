#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Settings.hpp"
#include "Ground.hpp"

class Planet
{
private:
    vector<vector<shared_ptr<Ground>>> grid;

    sf::Sprite ground_sprite;

    b2BodyDef ground_body_def;
    b2Body *ground_body;

public:
    Planet(b2World &world);
    ~Planet();

    void draw(sf::RenderWindow &window, sf::Vector2f _position);
    void update(float delta_time);
    void generateFromImage();

    vector<shared_ptr<Ground>> getTilesByRange(sf::Vector2f _position, unsigned int _range);
};
