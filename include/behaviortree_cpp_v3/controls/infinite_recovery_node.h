//
// Created by Qianle Li on 2021/9/16.
//
/*
 * 无限制的尝试第二个节点，除非第一个节点成功
 * 注意，这意味着本控制节点永远不会返回FAILURE
 */

#ifndef BEHAVIORTREE_CPP_V3_INFINITE_RECOVERY_NODE_H
#define BEHAVIORTREE_CPP_V3_INFINITE_RECOVERY_NODE_H

#include <string>
#include "behaviortree_cpp_v3/control_node.h"

namespace BT
{
class InfiniteRecoveryNode : public BT::ControlNode
{
  public:
    InfiniteRecoveryNode(
        const std::string & name,
        const BT::NodeConfiguration & conf);

    ~InfiniteRecoveryNode() override = default;

    static BT::PortsList providedPorts()
    {
        return {
            BT::InputPort<int>("number_of_retries", 1, "Number of retries")
        };
    }

  private:
    unsigned int current_child_idx_;

    BT::NodeStatus tick() override;

    void halt() override;
};

}

#endif   //BEHAVIORTREE_CPP_V3_INFINITE_RECOVERY_NODE_H
