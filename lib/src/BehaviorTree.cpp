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
SelectorNode::SelectorNode() : current_child_index(0){}

void SelectorNode::addChild(std::shared_ptr<BTNode> child)
{
    children.push_back(child);
}
    
NodeStatus SelectorNode::execute()
{
    for (size_t i = current_child_index; i < children.size(); ++i)
    {
        NodeStatus status = children[i]->execute();
        if (status == NodeStatus::RUNNING)
        {
            current_child_index = i;
            return NodeStatus::RUNNING;
        }
        if (status == NodeStatus::SUCCESS)
        {
            current_child_index = 0;
            return NodeStatus::SUCCESS;
        }
    }
    current_child_index = 0;
    return NodeStatus::FAILURE;
}

// Definiciones de SequenceNode
SequenceNode::SequenceNode() : current_child_index(0){}

void SequenceNode::addChild(std::shared_ptr<BTNode> child)
{
    children.push_back(child);
}

NodeStatus SequenceNode::execute()
{
    for (size_t i = current_child_index; i < children.size(); ++i)
    {
        NodeStatus status = children[i]->execute();
        if (status == NodeStatus::RUNNING)
        {
            current_child_index = i;
            return NodeStatus::RUNNING;
        }
        if (status == NodeStatus::FAILURE)
        {
            current_child_index = 0;
            return NodeStatus::FAILURE;
        }
    }
    current_child_index = 0;
    return NodeStatus::SUCCESS;
}
