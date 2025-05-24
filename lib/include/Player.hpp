#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <Coordinates.hpp>

class Player
{
private:
    PolarCoordinates coordinates;
    sf::Texture texture;
    sf::Sprite sprite;

    int health_points;
    int max_health;
    int attack_points;
    int attack_range;

    float SPEED = 50.0f;

    bool jumping;
    float jump_timer;
    bool grounded;
    bool free_movement;

public:
    Player();
    ~Player();
    sf::Vector2f getPosition();
    int getHealthPoints() const;
    void takeDamage(int damage);
    void draw(sf::RenderWindow &window) const;
    void update(float delta_time);
};
