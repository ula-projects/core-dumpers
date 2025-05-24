#pragma once

#include <vector>
#include <memory>

#include "BehaviorTree.hpp"
#include "Player.hpp"

class Enemy
{
public:
    Enemy(const sf::Texture& texture);
    virtual ~Enemy() = default;
    int getHealthPoints() const;
    int getVisionRange() const;
    sf::Vector2f getPosition() const;
    void takeDamage(int damage);
    void setTarget(std::shared_ptr<Player> _player);
    void update(float _delta_time);

    void draw(sf::RenderWindow &window);
    
protected:
    int health_points;
    int max_health;
    int attack_points;
    int drop;
    float attack_range;
    float vision_range;
    float speed;
    float delta_time;
    sf::Clock attack_clock;
    sf::Clock health_clock;
    float attack_cooldown;
    float regen_cooldown;
    std::shared_ptr<Player> target;
    sf::Sprite sprite;
    bool debug_options;
    std::shared_ptr<BTNode> behavior_tree;

    bool isPlayerNear();
    bool isPlayerInAttackRange();
    bool isHealthLow();

    bool checkTargetStatus();

    virtual NodeStatus attackPlayer() = 0;
    virtual NodeStatus approachPlayer() = 0;
    virtual NodeStatus rest() = 0;
    virtual NodeStatus patrolArea() = 0;

    std::shared_ptr<BTNode> createEnemyBehaviorTree();
};

class FlyingEnemy : public Enemy
{
public:
    FlyingEnemy(sf::Vector2f position, const sf::Texture& texture);
    ~FlyingEnemy() override = default;
private:
    NodeStatus attackPlayer() override;
    NodeStatus approachPlayer() override;
    NodeStatus rest() override;
    NodeStatus patrolArea() override;
};

void InteractionManager(std::vector<std::shared_ptr<Enemy>>& enemies, std::shared_ptr<Player> player);