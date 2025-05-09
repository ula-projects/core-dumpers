#include <SFML/Graphics.hpp>
#include <QuadTreeNode.hpp>
#include <memory>

/*
    alias
*/
template <typename T>
using shared_ptr = std::shared_ptr<T>;
template <typename T, std::size_t N>
using array = std::array<T, N>;

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
