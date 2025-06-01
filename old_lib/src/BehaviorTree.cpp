#include "BehaviorTree.hpp"

// Definiciones de ConditionNode
ConditionNode::ConditionNode(std::function<bool()> _condition) : condition(std::move(_condition)) {}
    
NodeStatus ConditionNode::execute()
{
    return condition() ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
}

// Definiciones de ActionNode
ActionNode::ActionNode(std::function<NodeStatus()> _action) : action(std::move(_action)) {}
    
NodeStatus ActionNode::execute()
{
    return action();
}

// Definiciones de SelectorNode
void SelectorNode::addChild(std::shared_ptr<BTNode> child)
{
    children.push_back(child);
}
    
NodeStatus SelectorNode::execute()
{
    for (auto& child : children)
    {
        NodeStatus status = child->execute();
        if (status == NodeStatus::RUNNING)
        {
            return NodeStatus::RUNNING;
        }
        if (status == NodeStatus::SUCCESS)
        {
            return NodeStatus::SUCCESS;
        }
    }
    return NodeStatus::FAILURE;
}


// Definiciones de SequenceNode
void SequenceNode::addChild(std::shared_ptr<BTNode> child)
{
    children.push_back(child);
}

NodeStatus SequenceNode::execute()
{
    for (auto& child : children)
    {
        NodeStatus status = child->execute();
        if (status == NodeStatus::RUNNING)
        {
            return NodeStatus::RUNNING;
        }
        if (status == NodeStatus::FAILURE)
        {
            return NodeStatus::FAILURE;
        }
    }
    return NodeStatus::SUCCESS;
}
