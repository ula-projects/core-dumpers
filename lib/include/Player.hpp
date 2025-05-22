#include <SFML/Graphics.hpp>
#include <Coordinates.hpp>
#include <QuadTreeNode.hpp>
#include <OBB.hpp>

class Player
{
private:
    PolarCoordinates coordinates;
    sf::Texture texture;
    sf::Sprite sprite;
    int health_points;
    float SPEED = 50.0f;

    OBB player_boundary;
    bool jumping;
    float jump_timer;
    float sprite_time;
    int current_sprite;
    bool grounded;
    bool free_movement;

public:
    Player();
    ~Player();
    sf::Vector2f getPosition();
    void draw(sf::RenderWindow &window) const;
    void update(float delta_time, vector<shared_ptr<QuadTreeNode>> collision_list, sf::RenderWindow &window);
    int getHealthPoints() const;
    void takeDamage(int damage);
};
