#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <array>
#include <memory>

/*
    alias
*/
template <typename T>
using shared_ptr = std::shared_ptr<T>;
template <typename T>
using vector = std::vector<T>;
template <typename T, std::size_t N>
using array = std::array<T, N>;

/*
    Region
*/
struct Region
{
    float pos_x;
    float pos_y;
    float size;
    Region();
    Region(float _x, float _y, float _size);

    bool isRegionInsideCircle(const float &_radius);
    bool isCenterInsideCircle(const float &_radius);
    bool isRegionOutsideCircle(const float &_radius);
};

/*
    Quad Tree Node
*/
class QuadTreeNode
{
private:
    Region region;
    array<shared_ptr<QuadTreeNode>, 4> sub_regions;
    int depth;
    bool is_leaf;
    bool is_empty;

public:
    QuadTreeNode(const Region &_region);
    ~QuadTreeNode();
    void subdivide(int _depth);
    void draw(sf::RenderWindow &window) const;
};

/*
    Quad Tree
*/

class QuadTree
{
private:
    shared_ptr<QuadTreeNode> root;

public:
    QuadTree();
    ~QuadTree();
    void draw(sf::RenderWindow &window) const;
};
