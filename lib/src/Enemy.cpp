#include "Enemy.hpp"

Enemy::Enemy() : sprite(texture){}

void Enemy::takeDamage(int damage)
{
    health_points -= damage;

    if (health_points <= 0)
    {
        // asignar drop al jugador
        health_points = 0;
    }
}

int Enemy::getHealthPoints() const
{
    return health_points;
}

int Enemy::getVisionRange() const
{
    return vision_range;
}

sf::Vector2f Enemy::getPosition() const
{
    return sprite.getPosition();
}

void Enemy::setTarget(std::shared_ptr<Player> _player)
{
    if (_player)
    {
        target = _player;
    }
}

bool Enemy::checkTargetStatus()
{
    if (target == nullptr)
    {
        return false;
    }

    if (target->getHealthPoints() <= 0)
    {
        target.reset();
        return false;
    }
    return true;
}

void Enemy::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
    vision_area.setPosition(getPosition());
    attack_area.setPosition(getPosition());

    if (debug_options)
    {
        window.draw(vision_area);
        window.draw(attack_area);
    }
}

// Implementaciones de funciones condicion
bool Enemy::isPlayerNear()
{
    if(!checkTargetStatus())
    {
        return false;
    }

    float distance = std::hypot(target->getPosition().x - getPosition().x, target->getPosition().y - getPosition().y);
    if (distance < vision_range)
    {
        return true;
    }
    return false;
}

bool Enemy::isPlayerInAttackRange()
{
    if(!checkTargetStatus())
    {
        return false;
    }
    
    float distance = std::hypot(target->getPosition().x - getPosition().x, target->getPosition().y - getPosition().y);
    if (distance < attack_range)
    {
        return true;
    }
    return false;
}

bool Enemy::isHealthLow()
{
    if (health_points < max_health / 4)
    {
        return true;
    }
    return false;
}

// Implementacion del arbol de comportamiento del enemy
std::shared_ptr<BTNode> Enemy::createEnemyBehaviorTree()
{
    // Comportamiento principal - Selector
    auto main_behavior = std::make_shared<SelectorNode>();
    
    // Primera rama: Secuencia para comportamiento de combate
    auto combat_sequence = std::make_shared<SequenceNode>();
    {
        // Condicion: Enemigo cerca?
        combat_sequence->addChild(std::make_shared<ConditionNode>([this]() {return isPlayerNear();}));
        
        // Selector para decidir que hacer con el enemigo cercano
        auto enemy_action_selector = std::make_shared<SelectorNode>();
        {
            // Opcion 1: Secuencia para atacar si esta al alcance
            auto attack_sequence = std::make_shared<SequenceNode>();
            {
                // Condicion: Enemigo al alcance de ataque?
                attack_sequence->addChild(std::make_shared<ConditionNode>([this]() {return isPlayerInAttackRange();}));
                
                // Accion: Atacar al enemigo
                attack_sequence->addChild(std::make_shared<ActionNode>([this]() {return attackPlayer();}));
            }
            
            // Opcion 2: Acercarse al enemigo si no esta al alcance
            auto approach_action = std::make_shared<ActionNode>([this]() {return approachPlayer();});
            
            enemy_action_selector->addChild(attack_sequence);
            enemy_action_selector->addChild(approach_action);
        }
        
        combat_sequence->addChild(enemy_action_selector);
    }
    
    // Segunda rama: Selector para comportamiento cuando no hay enemigos cerca
    auto idle_selector = std::make_shared<SelectorNode>();
    {
        // Opcion 1: Secuencia para descansar si tiene poca vida
        auto rest_sequence = std::make_shared<SequenceNode>();
        {
            // Condicion: Tiene poca vida?
            rest_sequence->addChild(std::make_shared<ConditionNode>([this]() {return isHealthLow();}));
            
            // Accion: Descansar para recuperar vida
            rest_sequence->addChild(std::make_shared<ActionNode>([this]() {return rest();}));
        }
        
        // Opcion 2: Patrullar la zona si no tiene poca vida
        auto patrol_action = std::make_shared<ActionNode>([this]() {return patrolArea();});
        
        idle_selector->addChild(rest_sequence);
        idle_selector->addChild(patrol_action);
    }
    
    // Anadir ambas ramas al comportamiento principal
    main_behavior->addChild(combat_sequence);
    main_behavior->addChild(idle_selector);
    
    return main_behavior;
}

void Enemy::update(float _delta_time)
{
    delta_time = _delta_time;
    NodeStatus status = behavior_tree->execute();

    if (status == NodeStatus::SUCCESS || status == NodeStatus::FAILURE)
    {
        behavior_tree = createEnemyBehaviorTree();
    }

}

FlyingEnemy::FlyingEnemy(sf::Vector2f position)
{
    health_points = 100;
    max_health = 100;
    attack_points = 10;
    drop = 25;
    attack_range = 50;
    vision_range = 250;
    speed = 50.0f;
    debug_options  = false;
    delta_time = 0.0f;
    attack_cooldown = 1.0f;
    regen_cooldown = 1.0f;

    behavior_tree = createEnemyBehaviorTree();

    if (!texture.loadFromFile("enemy.png"))
    {
        // Error cargando la textura
    }
    sprite.setTexture(texture);
    sprite.setOrigin({8, 8});
    sprite.setPosition(position);

    //Debug Options
    vision_area.setRadius(vision_range);
    vision_area.setFillColor(sf::Color::Transparent);
    vision_area.setOutlineColor(sf::Color::Yellow);
    vision_area.setOutlineThickness(1.5f);

    if (vision_area.getOrigin().x == 0.0f && vision_area.getOrigin().y == 0.0f)
    {
        vision_area.setOrigin({vision_area.getRadius(), vision_area.getRadius()});
    }

    vision_area.setPosition(getPosition());

    attack_area.setRadius(attack_range);
    attack_area.setFillColor(sf::Color::Transparent);
    attack_area.setOutlineColor(sf::Color::Magenta);
    attack_area.setOutlineThickness(1.5f);

    if (attack_area.getOrigin().x == 0.0f && attack_area.getOrigin().y == 0.0f)
    {
        attack_area.setOrigin({attack_area.getRadius(), attack_area.getRadius()});
    }

    attack_area.setPosition(getPosition());
}

NodeStatus FlyingEnemy::attackPlayer()
{
    if(!checkTargetStatus())
    {
        return NodeStatus::FAILURE;
    }

    // Atacar al objetivo
    if (attack_clock.getElapsedTime().asSeconds() >= attack_cooldown)
    {
        target->takeDamage(attack_points);
        attack_clock.restart();

        checkTargetStatus();
        return NodeStatus::SUCCESS;
    }
    return NodeStatus::RUNNING;
}

NodeStatus FlyingEnemy::approachPlayer()
{
    if(!checkTargetStatus())
    {
        return NodeStatus::FAILURE;
    }
    
    // Acercarse al objetivo
    sf::Vector2f enemy_position = getPosition();
    sf::Vector2f target_position = target->getPosition();

    sf::Vector2f direction = target_position - enemy_position;
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude > attack_range - 25.0f)
    {
        direction /= magnitude;
        sprite.move(direction * speed * delta_time);
        return NodeStatus::RUNNING;
    }

    return NodeStatus::SUCCESS;
}

NodeStatus FlyingEnemy::rest()
{
    checkTargetStatus();
    if (health_clock.getElapsedTime().asSeconds() >= regen_cooldown)
    {
        if (health_points < max_health)
        {
            health_points += 1;
            health_clock.restart();
            return NodeStatus::RUNNING;
        }
        return NodeStatus::SUCCESS;
    }
    return NodeStatus::FAILURE;
}

NodeStatus FlyingEnemy::patrolArea()
{
    checkTargetStatus();
    return NodeStatus::SUCCESS;
}

void InteractionManager(std::vector<std::shared_ptr<Enemy>>& enemies, std::shared_ptr<Player> player)
{
    for (auto& enemy : enemies)
    {
        if (enemy->getHealthPoints() > 0 && player->getHealthPoints() > 0)
        {
            float distance = std::hypot(player->getPosition().x - enemy->getPosition().x, player->getPosition().y - enemy->getPosition().y);
            if (distance < enemy->getVisionRange())
            {
                enemy->setTarget(player);
            }
        }
    }
}