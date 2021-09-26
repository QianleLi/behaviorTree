//
// Created by Qianle Li on 2021/9/16.
//
/*
 * 只要第二个节点成功就无限制的尝试第二个节点，除非第一个节点成功
 * 如果第二个节点失败则返回FAILURE
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
        return {};
    }

  private:
    unsigned int current_child_idx_;

    const unsigned children_count = 2;      //recovery 必然有两个子节点

    BT::NodeStatus tick() override;

    void halt() override;
};

}

#endif   //BEHAVIORTREE_CPP_V3_INFINITE_RECOVERY_NODE_H
