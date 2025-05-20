#pragma once

#include <SFML/Graphics.hpp>
#include <Player.hpp>
#include <QuadTree.hpp>
#include <Planet.hpp>
#include <Camera.hpp>
#include <Menu.hpp>

class Game
{
private:
    QuadTree qt;
    Player player;
    Camera camera;
    XY world_center;
    AABB world_boundary;
    Menu menu;

    int game_state;

public:
    Game();
    void draw(sf::RenderWindow &window);
    void update(float &delta_time, sf::RenderWindow &window);
};