#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <memory>
#include <AABB.hpp>

template <typename T>
using shared_ptr = std::shared_ptr<T>;
template <typename T, std::size_t N>
using array = std::array<T, N>;

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
    void draw(sf::RenderWindow &window) const;
};