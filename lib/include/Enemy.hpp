#pragma once

#include "Settings.hpp"
#include "BehaviorTree.hpp"
#include "Player.hpp"
#include "PolarCoordinates.hpp"

class Enemy
{
protected:
    PolarCoordinates coordinates;
    sf::Sprite sprite;
    b2Body *enemy_b2_body;
    float health_points;
    float max_health;
    float attack_points;
    float attack_range;
    float vision_range;

    float attack_cooldown;
    float regen_cooldown;

    std::shared_ptr<Player> target;

    bool debug_options;
    std::shared_ptr<BTNode> behavior_tree_root;

    bool isPlayerNear();
    bool isPlayerInAttackRange();
    bool isHealthLow();

    bool checkTargetStatus();

    virtual NodeStatus attackPlayer() = 0;
    virtual NodeStatus approachPlayer() = 0;
    virtual NodeStatus rest() = 0;
    virtual NodeStatus patrolArea() = 0;

    sf::Clock action_clock;

    std::shared_ptr<BTNode> createEnemyBehaviorTree();

    b2World *world_ref;

public:
    Enemy();
    sf::CircleShape hitbox;
    virtual ~Enemy() = default;
    int getHealthPoints() const;
    int getVisionRange() const;
    sf::Vector2f getPosition() const;
    void takeDamage(int damage);
    void setTarget(std::shared_ptr<Player> _player);
    void update();
    void init(b2World &world, sf::Vector2f init_position);

    void draw(sf::RenderWindow &window);
};

class FlyingEnemy : public Enemy
{
public:
    FlyingEnemy(sf::Vector2f position);
    ~FlyingEnemy() override = default;

private:
    int direction;
    NodeStatus attackPlayer() override;
    NodeStatus approachPlayer() override;
    NodeStatus rest() override;
    NodeStatus patrolArea() override;
};

void InteractionManager(std::vector<std::shared_ptr<Enemy>> &enemies, std::shared_ptr<Player> player);
