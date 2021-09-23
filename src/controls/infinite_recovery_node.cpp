//
// Created by Qianle Li on 2021/9/16.
//

#include <thread>
#include "behaviortree_cpp_v3/controls/infinite_recovery_node.h"

namespace BT
{

InfiniteRecoveryNode::InfiniteRecoveryNode(
    const std::string & name,
    const BT::NodeConfiguration & conf)
    : BT::ControlNode::ControlNode(name, conf),
      current_child_idx_(0)
{
    setRegistrationID("InfiniteRecoveryNode");
}

BT::NodeStatus InfiniteRecoveryNode::tick()
{
    if (children_nodes_.size() != 2) {
        throw BT::BehaviorTreeException("Recovery Node '" + name() + "' must only have 2 children.");
    }
    if(current_child_idx_ >= children_count)
        return BT::NodeStatus::FAILURE;

    setStatus(BT::NodeStatus::RUNNING);

    TreeNode * child_node = children_nodes_[current_child_idx_];
    const BT::NodeStatus child_status = child_node->executeTick();

    if (current_child_idx_ == 0) {
        switch (child_status) {
            case BT::NodeStatus::SUCCESS:
            {
                // reset node and return success when first child returns success
                halt();
                return BT::NodeStatus::SUCCESS;
            }

            case BT::NodeStatus::FAILURE:
            {
                // halt first child and tick second child in next iteration
                ControlNode::haltChild(0);
                std::cout << "First child failed" << std::endl;
                current_child_idx_++;
                return BT::NodeStatus::RUNNING;
            }

            case BT::NodeStatus::RUNNING:
            {
                return BT::NodeStatus::RUNNING;
            }

            default:
            {
                throw BT::LogicError("A child node must never return IDLE");
            }
        }  // end switch

    } else if (current_child_idx_ == 1) {
        switch (child_status) {
            case BT::NodeStatus::SUCCESS:
            {
                // 第二个节点成功后再次尝试第一个节点
                ControlNode::haltChild(1);
                current_child_idx_--;
                return BT::NodeStatus::RUNNING;
            }

            case BT::NodeStatus::FAILURE://如果失败下一次继续tick第二个
            {
                ControlNode::haltChild(1);
                return BT::NodeStatus::RUNNING;
            }
            case BT::NodeStatus::RUNNING:
            {
                return BT::NodeStatus::RUNNING;
            }

            default:
            {
                throw BT::LogicError("A child node must never return IDLE");
            }
        }  // end switch
    }
    return BT::NodeStatus::RUNNING;
}

void InfiniteRecoveryNode::halt()
{
    ControlNode::halt();
    current_child_idx_ = 0;
}

}