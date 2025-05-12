#include <QuadTreeNode.hpp>

/*
    Region
*/
Region::Region()
{
    pos_x = pos_y = size = 0.0f;
}

Region::Region(float _x, float _y, float _size)
{
    pos_x = _x;
    pos_y = _y;
    size = _size;
}

bool Region::isRegionInsideCircle(const float &_radius)
{
    float half = size / 2;

    float corners[4][2] = {
        {pos_x - half, pos_y - half},  // Bottom-Left
        {pos_x + half, pos_y - half},  // Bottom-Right
        {pos_x - half, pos_x + half},  // Top-Left
        {pos_x + half, pos_y + half}}; // Top-Right

    for (auto &corner : corners)
    {
        float x = corner[0];
        float y = corner[1];
        if (std::sqrt(std::pow(x, 2) + std::pow(y, 2)) > _radius)
            return false;
    }

    return true;
}

bool Region::isCenterInsideCircle(const float &_radius)
{
    return std::sqrt(std::pow(std::abs(pos_x), 2) + std::pow(std::abs(pos_x), 2)) <= _radius;
}

bool Region::isRegionOutsideCircle(const float &_radius)
{
    float half = size / 2;
    float cx = std::abs(pos_x) - half;
    float cy = std::abs(pos_y) - half;
    return std::sqrt(std::pow(cx, 2) + std::pow(cy, 2)) > _radius;
}

/*
    Quad Tree Node
*/

QuadTreeNode::QuadTreeNode(const Region &_region)
{
    region = _region;
    is_leaf = is_empty = false;

    for (auto sub_reg : sub_regions)
    {
        sub_reg = nullptr;
    }
}

QuadTreeNode::~QuadTreeNode()
{
}

void QuadTreeNode::subdivide(int _depth)
{
    depth = _depth;
    if (_depth >= 5)
    {
        is_leaf = true;
        if (region.isRegionOutsideCircle(256.0f))
        {
            is_empty = true;
        }
        return;
    }
    float half = region.size / 2;
    float quarter = region.size / 4;

    Region regions[4] = {
        Region(region.pos_x - quarter, region.pos_y - quarter, half),
        Region(region.pos_x + quarter, region.pos_y - quarter, half),
        Region(region.pos_x - quarter, region.pos_y + quarter, half),
        Region(region.pos_x + quarter, region.pos_y + quarter, half),
    };

    for (int i = 0; i < 4; ++i)
    {
        sub_regions[i] = std::make_shared<QuadTreeNode>(regions[i]);
        sub_regions[i]->subdivide(_depth + 1);
    }
}

void QuadTreeNode::draw(sf::RenderWindow &window) const
{
    if (is_leaf)
    {
        sf::RectangleShape square;
        square.setSize({region.size, region.size});
        square.setOrigin({region.size / 2, region.size / 2});
        square.setPosition({region.pos_x + 1024 / 2, region.pos_y + 1024 / 2});
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
        for (auto sub_reg : sub_regions)
        {
            sub_reg->draw(window);
        }
    }
};