#pragma once

#include <SFML/Graphics.hpp>
#include <Player.hpp>
#include <QuadTree.hpp>
#include <Planet.hpp>
#include <Camera.hpp>

class Game
{
private:
    QuadTree qt;
    Player player;
    Camera camera;

public:
    Game();
    void draw(sf::RenderWindow &window) const;
    void update(float &delta_time);
};