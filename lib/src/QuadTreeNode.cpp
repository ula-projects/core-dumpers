#include <QuadTreeNode.hpp>

QuadTreeNode::QuadTreeNode(const AABB &_boundary)
{
    boundary = _boundary;
    is_leaf = is_empty = false;

    north_west = north_east = south_west = south_east = nullptr;
}

QuadTreeNode::~QuadTreeNode()
{
}

void QuadTreeNode::subdivide(XY _world_center, int _depthness)
{
    depthness = _depthness;

    if (boundary.isRegionOutsideCircle(_world_center, 256.0f))
    {
        is_leaf = true;
        is_empty = true;
        return;
    }

    if (_depthness >= 6)
    {
        is_leaf = true;
        return;
    }

    float quarter = boundary.half_width / 2;

    north_west = std::make_shared<QuadTreeNode>(AABB(XY(boundary.center.x - quarter, boundary.center.y - quarter), quarter, quarter));
    north_east = std::make_shared<QuadTreeNode>(AABB(XY(boundary.center.x + quarter, boundary.center.y - quarter), quarter, quarter));
    south_west = std::make_shared<QuadTreeNode>(AABB(XY(boundary.center.x - quarter, boundary.center.y + quarter), quarter, quarter));
    south_east = std::make_shared<QuadTreeNode>(AABB(XY(boundary.center.x + quarter, boundary.center.y + quarter), quarter, quarter));

    north_west->subdivide(_world_center, _depthness + 1);
    north_east->subdivide(_world_center, _depthness + 1);
    south_west->subdivide(_world_center, _depthness + 1);
    south_east->subdivide(_world_center, _depthness + 1);
}

void QuadTreeNode::draw(sf::RenderWindow &window, shared_ptr<sf::Sprite> &ground) const
{
    if (is_leaf)
    {
        ground->setPosition({boundary.center.x, boundary.center.y});
        if (!is_empty)
        {

            window.draw(*ground);
        }
    }
    else
    {
        north_west->draw(window, ground);
        north_east->draw(window, ground);
        south_west->draw(window, ground);
        south_east->draw(window, ground);
    }
}

vector<shared_ptr<QuadTreeNode>> QuadTreeNode::queryRange(AABB &_boundary, shared_ptr<QuadTreeNode> &_this_ptr)
{
    vector<shared_ptr<QuadTreeNode>> list;

    if (!boundary.intersectsAABB(_boundary))
    {
        return list;
    }

    if (!is_leaf)
    {
        vector<shared_ptr<QuadTreeNode>> nw_list = north_west->queryRange(_boundary, north_west);
        vector<shared_ptr<QuadTreeNode>> ne_list = north_east->queryRange(_boundary, north_east);
        vector<shared_ptr<QuadTreeNode>> sw_list = south_west->queryRange(_boundary, south_west);
        vector<shared_ptr<QuadTreeNode>> se_list = south_east->queryRange(_boundary, south_east);
        list.insert(list.end(), nw_list.begin(), nw_list.end());
        list.insert(list.end(), ne_list.begin(), ne_list.end());
        list.insert(list.end(), sw_list.begin(), sw_list.end());
        list.insert(list.end(), se_list.begin(), se_list.end());
    }

    if (is_leaf && depthness >= 6)
    {
        list.push_back(_this_ptr);
    }

    return list;
}

bool QuadTreeNode::collisionAABB(AABB _boundary)
{
    return boundary.intersectsAABB(_boundary);
}