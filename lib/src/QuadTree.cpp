#include <QuadTree.hpp>

/*
    Quad Tree
*/
QuadTree::QuadTree()
{
    Region rootRegion(0, 0, 1024);
    root = std::make_shared<QuadTreeNode>(rootRegion);
    root->subdivide(0);
}

QuadTree::~QuadTree() {}

void QuadTree::draw(sf::RenderWindow &window) const
{
    root->draw(window);
};
