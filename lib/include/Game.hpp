#pragma once

#include <SFML/Graphics.hpp>
#include <Player.hpp>
#include <QuadTree.hpp>
#include <Planet.hpp>

class Game
{
private:
    QuadTree qt;

public:
    Game() noexcept;
    void draw(sf::RenderWindow &window) const;
};