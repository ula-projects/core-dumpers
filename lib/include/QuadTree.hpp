#include <SFML/Graphics.hpp>
#include <vector>

class QuadTree
{
private:
public:
    QuadTree();
    ~QuadTree();
    void drawByQuery();
    void generateWorld();
};

// #include <SFML/Graphics.hpp>
// #include <QuadTreeNode.hpp>

// class QuadTree
// {
// private:
//     shared_ptr<QuadTreeNode> root;
//     XY world_center;

// public:
//     QuadTree();
//     QuadTree(AABB _boundary);
//     ~QuadTree();
//     void draw(sf::RenderWindow &window, shared_ptr<sf::Sprite> &ground) const;
//     void setBoundary(AABB _boundary);
//     void generateWorld();
//     vector<shared_ptr<QuadTreeNode>> queryRange(AABB &_boundary);
// };
