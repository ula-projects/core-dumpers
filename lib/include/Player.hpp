#pragma once
#include "Settings.hpp"
#include <box2d/box2d.h>
#include "PolarCoordinates.hpp"

class Player
{
private:
    PolarCoordinates coordinates;

    sf::Sprite sprite;

    b2Body *player_b2_body;
    bool is_grounded;
    bool is_jumping;
    bool free_movement;
    float sprite_time;
    int current_sprite;

    int health_points;
    int max_health;
    int attack_points;
    float attack_range;

public:
    Player();
    ~Player();

    void update(float delta_time);
    void draw(sf::RenderWindow &window);
    void init(b2World &world);
    sf::Vector2f getPosition();
    PolarCoordinates getCoordinates();
    int getHealthPoints() const;
    void takeDamage(int damage);
    void setIsGrounded(bool _grounded);
};
