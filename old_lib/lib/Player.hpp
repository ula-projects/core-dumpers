#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Settings.hpp"

class Player
{
private:
    sf::Sprite player_sprite;

public:
    Player();
    ~Player();
    void update(float _delta_time);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition();
};

// class Player
// {
// private:
//     PolarCoordinates coordinates;
//     sf::Texture texture;
//     sf::Sprite sprite;
//     int health_points;
//     float SPEED = 50.0f;

//     OBB player_boundary;
//     bool jumping;
//     float jump_timer;
//     float sprite_time;
//     int current_sprite;
//     bool grounded;
//     bool free_movement;

// public:
//     Player();
//     ~Player();
//     sf::Vector2f getPosition();
//     void draw(sf::RenderWindow &window) const;
//     void update(float delta_time, vector<shared_ptr<QuadTreeNode>> collision_list, sf::RenderWindow &window);
//     int getHealthPoints() const;
//     void takeDamage(int damage);
// };
