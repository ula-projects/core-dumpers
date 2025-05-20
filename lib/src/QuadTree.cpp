#include <QuadTree.hpp>

QuadTree::QuadTree()
{
    root = nullptr;
}

QuadTree::QuadTree(AABB _boundary)
{
    root = std::make_shared<QuadTreeNode>(_boundary);
    world_center = _boundary.center;
    generateWorld();
}

QuadTree::~QuadTree() {}

void QuadTree::draw(sf::RenderWindow &window) const
{
    root->draw(window);
};

void QuadTree::setBoundary(AABB _boundary)
{
    root = std::make_shared<QuadTreeNode>(_boundary);
    world_center = _boundary.center;
    // if (root == nullptr)
    // {
    // }
}

void QuadTree::generateWorld()
{
    root->subdivide(world_center, 0);
}