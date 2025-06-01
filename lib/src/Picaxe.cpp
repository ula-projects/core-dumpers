#include "Picaxe.hpp"

Picaxe::Picaxe()
{
}

Picaxe::~Picaxe()
{
}

void Picaxe::update(sf::RenderWindow &window, vector<shared_ptr<Ground>> ground_list)
{

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        for (auto tile : ground_list)
        {
            sf::Vector2i click_pos = sf::Mouse::getPosition(window);
            sf::Vector2f absolute_pos = window.mapPixelToCoords(click_pos);
            tile->destroyTile(absolute_pos);
        }
        // for (auto ground : collision_list)
        // {

        //     if (ground->getBoundary().containsXY(XY(absolute_pos.x, absolute_pos.y)))
        //     {
        //         ground->undermine();
        //     }
        // }
    }
}