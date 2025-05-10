#pragma once

#include <SFML/Graphics.hpp>
#include <Player.hpp>
#include <QuadTree.hpp>
#include <Planet.hpp>

class Game
{
private:
    QuadTree qt;
    Player player;

public:
    Game();
    void draw(sf::RenderWindow &window) const;
    void update(float &delta_time);
};