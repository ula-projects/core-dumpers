#pragma once
#include <SFML/Graphics.hpp>
#include <AABB.hpp>
#include <memory>
#include <vector>

template <typename T>
using shared_ptr = std::shared_ptr<T>;
template <typename T>
using vector = std::vector<T>;

class QuadTreeNode
{
private:
    AABB boundary;

    shared_ptr<QuadTreeNode> north_west;
    shared_ptr<QuadTreeNode> north_east;
    shared_ptr<QuadTreeNode> south_west;
    shared_ptr<QuadTreeNode> south_east;

    int depthness;
    bool is_leaf;
    bool is_empty;

public:
    QuadTreeNode(const AABB &_boundary);
    ~QuadTreeNode();

    void subdivide(XY _world_center, int _depthness);
    void draw(sf::RenderWindow &window, shared_ptr<sf::Sprite> &ground) const;
    vector<shared_ptr<QuadTreeNode>> queryRange(AABB &_boundary, shared_ptr<QuadTreeNode> &_this_ptr);
    AABB getBoundary();
    bool getIsEmpty();
    bool collisionAABB(AABB _boundary);
    void undermine();
};