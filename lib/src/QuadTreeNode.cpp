#include <QuadTreeNode.hpp>
/*
    Quad Tree Node
*/

QuadTreeNode::QuadTreeNode(const AABB &_boundary)
{
    boundary = _boundary;
    is_leaf = is_empty = false;

    north_west = north_east = south_west = south_east = nullptr;
}

QuadTreeNode::~QuadTreeNode()
{
}

void QuadTreeNode::subdivide(XY _world_center, int _depthness)
{
    depthness = _depthness;

    if (boundary.isRegionOutsideCircle(_world_center, 256.0f))
    {
        is_leaf = true;
        is_empty = true;
        return;
    }

    if (_depthness >= 7)
    {
        is_leaf = true;
        return;
    }

    float half = boundary.half_dimension / 2;
    float quarter = boundary.half_dimension / 2;

    north_west = std::make_shared<QuadTreeNode>(AABB(XY(boundary.center.x - quarter, boundary.center.y - quarter), half));
    north_east = std::make_shared<QuadTreeNode>(AABB(XY(boundary.center.x + quarter, boundary.center.y - quarter), half));
    south_west = std::make_shared<QuadTreeNode>(AABB(XY(boundary.center.x - quarter, boundary.center.y + quarter), half));
    south_east = std::make_shared<QuadTreeNode>(AABB(XY(boundary.center.x + quarter, boundary.center.y + quarter), half));

    north_west->subdivide(_world_center, _depthness + 1);
    north_east->subdivide(_world_center, _depthness + 1);
    south_west->subdivide(_world_center, _depthness + 1);
    south_east->subdivide(_world_center, _depthness + 1);
}

void QuadTreeNode::draw(sf::RenderWindow &window) const
{
    if (is_leaf)
    {
        sf::RectangleShape square;
        square.setSize({boundary.half_dimension * 2, boundary.half_dimension * 2});
        square.setOrigin({boundary.half_dimension, boundary.half_dimension});
        square.setPosition({boundary.center.x, boundary.center.y});
        square.setFillColor(sf::Color::Blue);
        if (is_empty)
        {
            square.setFillColor(sf::Color::White);
        }
        square.setOutlineColor(sf::Color::Black);
        square.setOutlineThickness(-0.5f);
        window.draw(square);
    }
    else
    {
        north_west->draw(window);
        north_east->draw(window);
        south_west->draw(window);
        south_east->draw(window);
    }
}
