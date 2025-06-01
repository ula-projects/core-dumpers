#include "Enemy.hpp"

Enemy::Enemy(const sf::Texture& texture) : sprite(texture){}

void Enemy::takeDamage(int damage)
{
    health_points -= damage;

    sprite.setColor(sf::Color(255, 100, 100, sprite.getColor().a)); // Aplicar modificador de color
    
    if (health_points <= 0)
    {
        // asignar drop al player
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

    if (debug_options)
    {
        sf::CircleShape vision_area;
        sf::CircleShape attack_area;
        vision_area.setRadius(vision_range);
        vision_area.setFillColor(sf::Color::Transparent);
        vision_area.setOutlineColor(sf::Color::Yellow);
        vision_area.setOutlineThickness(1.0f);
        vision_area.setOrigin({vision_range, vision_range});
        vision_area.setPosition(getPosition());
        attack_area.setRadius(attack_range);
        attack_area.setFillColor(sf::Color::Transparent);
        attack_area.setOutlineColor(sf::Color::Magenta);
        attack_area.setOutlineThickness(1.0f);
        attack_area.setOrigin({attack_range, attack_range});
        attack_area.setPosition(getPosition());
        window.draw(vision_area);
        window.draw(attack_area);
    }
}

// Implementaciones de funciones condicion
bool Enemy::isPlayerNear()
{
    if (!checkTargetStatus())
    {
        return false;
    }

    float distance = std::hypot(target->getPosition().x - getPosition().x, target->getPosition().y - getPosition().y);
    if (distance < vision_range)
    {
        if (debug_options)
        {
            std::cout << "Player ha entrado en el area de vision de Enemy" << std::endl;
        }
        return true;
    }
    return false;
}

bool Enemy::isPlayerInAttackRange()
{
    if (!checkTargetStatus())
    {
        return false;
    }
    
    float distance = std::hypot(target->getPosition().x - getPosition().x, target->getPosition().y - getPosition().y);
    if (distance < attack_range)
    {
        if (debug_options)
        {
            std::cout << "Player ha entrado en el area de ataque de Enemy" << std::endl;
        }
        return true;
    }
    return false;
}

bool Enemy::isHealthLow()
{
    if (health_points < max_health)
    {
        if (debug_options)
        {
            std::cout << "Enemy tiene poca vida" << std::endl;
        }
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

void Enemy::update(const float& _delta_time)
{
    delta_time = _delta_time;
    behavior_tree->execute();

    coordinates.updateCoordinates(sprite.getPosition());
    sf::Angle rotation_angle = -sf::degrees(coordinates.angle - 90);
    sprite.setRotation(rotation_angle);
    if (action_clock.getElapsedTime().asSeconds() >= regen_cooldown / 3)
    {
        sprite.setColor(sf::Color(255, 255, 255, sprite.getColor().a)); // Restaurar color
    }
}

FlyingEnemy::FlyingEnemy(sf::Vector2f position, const sf::Texture& texture) : Enemy(texture)
{
    health_points = 100;
    max_health = 100;
    attack_points = 10;
    drop = 25;
    attack_range = 30;
    vision_range = 120;
    speed = 35.0f;
    debug_options  = true;
    delta_time = 0.0f;
    attack_cooldown = 1.0f;
    regen_cooldown = 2.0f;
    direction = 0;
    behavior_tree = createEnemyBehaviorTree();

    sprite.setOrigin({8, 8});
    sprite.setPosition(position);
}

NodeStatus FlyingEnemy::attackPlayer()
{
    if (!checkTargetStatus())
    {
        return NodeStatus::FAILURE;
    }

    // Atacar al objetivo
    if (action_clock.getElapsedTime().asSeconds() >= attack_cooldown)
    {
        target->takeDamage(attack_points);
        if (debug_options)
        {
            std::cout << "Enemy ha atacado a Player" << std::endl;
        }
        action_clock.restart();

        checkTargetStatus();
        return NodeStatus::SUCCESS;
    }

    if (debug_options)
    {
        std::cout << "El ataque de Enemy se retraso debido al Cooldown" << std::endl;
    }

    return NodeStatus::RUNNING;
}

NodeStatus FlyingEnemy::approachPlayer()
{
    if (!checkTargetStatus())
    {
        return NodeStatus::FAILURE;
    }
    
    // Acercarse al objetivo
    sf::Vector2f enemy_position = getPosition();
    sf::Vector2f target_position = target->getPosition();

    sf::Vector2f direction = target_position - enemy_position;
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude > vision_range)
    {
        if (debug_options)
        {
            std::cout << "Approach interrumpido, Player ha salido del area de vision" << std::endl;
        }
        return NodeStatus::FAILURE;
    }

    if (magnitude > attack_range - 10.0f)
    {
        direction /= magnitude;
        sprite.move(direction * speed * delta_time);
        if (debug_options)
        {
            std::cout << "Enemy se esta acercando a Player" << std::endl;
        }
        return NodeStatus::RUNNING;
    }

    return NodeStatus::SUCCESS;
}

NodeStatus FlyingEnemy::rest()
{
    checkTargetStatus();

    if (isPlayerNear())
    {
        if (debug_options)
        {
            std::cout << "Rest interrumpido, Player ha entrado en el area de vision" << std::endl;
        }
        return NodeStatus::FAILURE;
    }

    if (action_clock.getElapsedTime().asSeconds() >= regen_cooldown)
    {
        if (health_points < max_health)
        {
            health_points += 3;
            sprite.setColor(sf::Color(150, 255, 150, sprite.getColor().a)); // Aplicar modificador de color verde

            if (health_points > max_health)
            {
                health_points = max_health;
            }

            if (debug_options)
            {
                std::cout << "Enemy ha regenerado vida, vida actual: " << getHealthPoints() << std::endl;
            }
            action_clock.restart();
            return NodeStatus::RUNNING;
        }
        return NodeStatus::SUCCESS;
    }
    return NodeStatus::RUNNING;
}

NodeStatus FlyingEnemy::patrolArea()
{
    if (isPlayerNear())
    {
        if (debug_options)
        {
            std::cout << "Patrol completado, Player ha entrado en el area de vision" << std::endl;
        }
        direction = 0;
        
        checkTargetStatus();
        return NodeStatus::SUCCESS;
    }
    else
    {
        if (debug_options)
        {
            std::cout << "Enemy esta patrullando la zona" << std::endl;
        }
        if (direction == 0)
        {
            direction = 1;
            action_clock.restart();
        }

        sf::Vector2f movement({0.0f, 0.0f});
        
        float patrol_cycle_time = 3.0f;
        if (action_clock.getElapsedTime().asSeconds() >= patrol_cycle_time)
        {
            direction *= -1;
            action_clock.restart();
        }

        if (direction == 1) //right
        {
            movement.x = std::cos(coordinates.rad_angle - (90 * M_PI / 180));
            movement.y = -std::sin(coordinates.rad_angle - (90 * M_PI / 180));
            if (debug_options)
            {
                std::cout << "Enemy patrulla a la derecha" << std::endl;
            }
        }

        if (direction == -1) //left
        {
            movement.x = std::cos(coordinates.rad_angle + (90 * M_PI / 180));
            movement.y = -std::sin(coordinates.rad_angle + (90 * M_PI / 180));
            if (debug_options)
            {
                std::cout << "Enemy patrulla a la izquierda" << std::endl;
            }
        }
        
        sprite.move(movement * speed * delta_time);
        checkTargetStatus();
        return NodeStatus::RUNNING;
    }
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