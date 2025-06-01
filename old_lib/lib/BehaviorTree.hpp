#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <functional>

enum class NodeStatus
{
    RUNNING,
    SUCCESS,
    FAILURE
};

// Declaracion de los nodos del arbol de comportamiento
class BTNode
{
public:
    virtual ~BTNode() = default;
    virtual NodeStatus execute() = 0;
};

class ConditionNode : public BTNode 
{
public:
    explicit ConditionNode(std::function<bool()> _condition);
    NodeStatus execute() override;

private:
    std::function<bool()> condition;
};

class ActionNode : public BTNode
{
public:
    explicit ActionNode(std::function<NodeStatus()> _action);
    NodeStatus execute() override;

private:
    std::function<NodeStatus()> action;
};

class SelectorNode : public BTNode
{
public:
    void addChild(std::shared_ptr<BTNode> child);
    NodeStatus execute() override;

private:
    std::vector<std::shared_ptr<BTNode>> children;
};

class SequenceNode : public BTNode
{
public:
    void addChild(std::shared_ptr<BTNode> child);
    NodeStatus execute() override;

private:
    std::vector<std::shared_ptr<BTNode>> children;
};