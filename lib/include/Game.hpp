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

    sf::Texture ground_texture;
    sf::Texture background_texture;
    sf::Sprite ground;
    sf::Sprite background;
    shared_ptr<sf::Sprite> ground_ptr;

    AABB view_boundary;
    vector<shared_ptr<QuadTreeNode>> ground_list;

    AABB collision_boundary;
    vector<shared_ptr<QuadTreeNode>> collision_list;

public:
    Game();
    void draw(sf::RenderWindow &window);
    void update(float &delta_time, sf::RenderWindow &window);
};