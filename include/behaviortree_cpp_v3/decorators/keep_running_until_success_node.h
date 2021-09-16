//
// Created by Qianle Li on 2021/9/7.
//

#ifndef DECORATOR_KEEP_RUNNING_UNTIL_SUCCESS_H
#define DECORATOR_KEEP_RUNNING_UNTIL_SUCCESS_H

#include "behaviortree_cpp_v3/decorator_node.h"

namespace BT {
/**
 * @brief The KeepRunningUntilFailureNode returns always FAILURE or RUNNING.
 */
class KeepRunningUntilSuccessNode : public DecoratorNode
{
  public:
    KeepRunningUntilSuccessNode(const std::string &name) : DecoratorNode(name, {})
    {
        setRegistrationID("KeepRunningUntilSuccess");
    }

  private:
    virtual BT::NodeStatus tick() override;
};

//------------ implementation ----------------------------

inline NodeStatus KeepRunningUntilSuccessNode::tick()
{
    setStatus(NodeStatus::RUNNING);

    const NodeStatus child_state = child_node_->executeTick();

    switch (child_state) {
        case NodeStatus::SUCCESS: {
            return NodeStatus::SUCCESS;
        }
        case NodeStatus::FAILURE:
        case NodeStatus::RUNNING: {
            return NodeStatus::RUNNING;
        }

        default: {
            return NodeStatus::RUNNING;
            // TODO throw?
        }
    }
    return status();
}
} // namespace BT

#endif
