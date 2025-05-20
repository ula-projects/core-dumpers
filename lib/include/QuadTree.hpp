#include <SFML/Graphics.hpp>
#include <QuadTreeNode.hpp>
#include <memory>

template <typename T>
using shared_ptr = std::shared_ptr<T>;
template <typename T, std::size_t N>
using array = std::array<T, N>;

class QuadTree
{
private:
    shared_ptr<QuadTreeNode> root;
    XY world_center;

public:
    QuadTree();
    QuadTree(AABB _boundary);
    ~QuadTree();
    void draw(sf::RenderWindow &window, shared_ptr<sf::Sprite> &ground) const;
    void setBoundary(AABB _boundary);
    void generateWorld();
};
