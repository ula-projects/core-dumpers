#pragma once

#include <SFML/Graphics.hpp>
#include <Player.hpp>
#include <Settings.hpp>
#include <Planet.hpp>
#include <box2d/box2d.h>
#include <array>
#include <vector>
#include <Camera.hpp>
#include <box2d/box2d.h>

enum class GameState
{
    MainMenu,
    Loading,
    Playing,
    Paused,
    GameOver,
    Victory,
    Settings,
    Exiting
};

class Game
{
private:
    // Mejorado
    GameState game_state;
    b2World world;
    b2Vec2 gravity;
    Planet planet;
    // Camera camera;
    // Player player;
    // vector<shared_ptr<QuadTreeNode>> collision_list;

public:
    Game();
    void draw(sf::RenderWindow &window);
    void update(float &delta_time, sf::RenderWindow &window);
};

// XY world_center;
// QuadTree qt;
// AABB world_boundary;
// Menu menu;

// sf::Texture ground_texture;
// sf::Texture background_texture;
// sf::Sprite ground;
// sf::Sprite background;
// shared_ptr<sf::Sprite> ground_ptr;

// AABB view_boundary;
// vector<shared_ptr<QuadTreeNode>> ground_list;

// AABB collision_boundary;