//
// Created by Qianle Li on 2021/9/16.
//

#include <thread>
#include "behaviortree_cpp_v3/controls/infinite_recovery_node.h"

namespace BT
{
InfiniteRecoveryNode::InfiniteRecoveryNode(const std::string& name,
                                           const BT::NodeConfiguration& conf)
  : BT::ControlNode::ControlNode(name, conf), current_child_idx_(0)
{
    setRegistrationID("InfiniteRecoveryNode");
}

BT::NodeStatus InfiniteRecoveryNode::tick()
{
    if (children_nodes_.size() != 2)
    {
        //        throw BT::BehaviorTreeException("Recovery Node '" + name() + "' must only have 2 children.");
        printf("Error! Recovery Node must only have 2 children");
    }

    setStatus(BT::NodeStatus::RUNNING);

    TreeNode* child_node1 = children_nodes_[0];
    const BT::NodeStatus child_status1 = child_node1->executeTick();
    switch (child_status1)
    {
        case BT::NodeStatus::SUCCESS: {
            // reset node and return success when first child returns success
            halt();
            return BT::NodeStatus::SUCCESS;
        }

        case BT::NodeStatus::FAILURE: {
            ControlNode::haltChild(0);
            break;
        }

        case BT::NodeStatus::RUNNING: {
            return BT::NodeStatus::RUNNING;
        }

        default: {
            //                throw BT::LogicError("A child node must never return IDLE");
            printf("A child node must never return IDLE");
        }
    }   // end switch

    TreeNode* child_node2 = children_nodes_[1];
    const BT::NodeStatus child_status2 = child_node2->executeTick();

    switch (child_status2)
    {
        case BT::NodeStatus::SUCCESS: {
            // 第二个节点成功后再次尝试第一个节点
            ControlNode::haltChild(1);
            return BT::NodeStatus::RUNNING;
        }

        case BT::NodeStatus::FAILURE:   //如果失败结束
        {
            //ControlNode::haltChild(1);
            return BT::NodeStatus::FAILURE;
        }
        case BT::NodeStatus::RUNNING: {
            return BT::NodeStatus::RUNNING;
        }

        default: {
            printf("A child node must never return IDLE");
        }
    }   // end switch

    return BT::NodeStatus::RUNNING;
}

void InfiniteRecoveryNode::halt()
{
    ControlNode::halt();
    current_child_idx_ = 0;
}

}   // namespace BT