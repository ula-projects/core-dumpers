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

void QuadTree::draw(sf::RenderWindow &window, shared_ptr<sf::Sprite> &ground) const
{
    root->draw(window, ground);
};

void QuadTree::setBoundary(AABB _boundary)
{
    root = std::make_shared<QuadTreeNode>(_boundary);
    world_center = _boundary.center;
}

void QuadTree::generateWorld()
{
    root->subdivide(world_center, 0);
}

vector<shared_ptr<QuadTreeNode>> QuadTree::queryRange(AABB &_boundary)
{
    return root->queryRange(_boundary, root);
}