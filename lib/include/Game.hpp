#pragma once

#include <SFML/Graphics.hpp>
#include <Player.hpp>
#include <QuadTree.hpp>
#include <Planet.hpp>
#include <Camera.hpp>
#include <Menu.hpp>
#include <Enemy.hpp>

class Game
{
private:
    QuadTree qt;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Enemy>> enemies;
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

    sf::Texture enemy_texture;
    

public:
    Game();
    void draw(sf::RenderWindow &window);
    void update(float &delta_time, sf::RenderWindow &window);
};