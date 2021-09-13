//
// Created by Qianle Li on 2021/9/13.
//

#include "behaviortree_cpp_v3/controls/one_frame_fallback.h"
namespace BT
{
OneFrameFallback::OneFrameFallback(const std::string& name) : BT::ControlNode(name, {})
{
    setRegistrationID("OneFrameFallback");
}

OneFrameFallback::OneFrameFallback(const std::string& name, const BT::NodeConfiguration& config)
  : BT::ControlNode(name, config)
{
    setRegistrationID("OneFrameFallback");
}

void OneFrameFallback::halt()
{
    BT::ControlNode::halt();
    last_child_ticked_ = 0;
}

BT::NodeStatus OneFrameFallback::tick()
{
    setStatus(BT::NodeStatus::RUNNING);
    // 每一帧都要执行所有的子节点，要求子节点要么返回SUCCESS要么返回FAILURE
    for (std::size_t i = 0; i < children_nodes_.size(); ++i)
    {
        auto status = children_nodes_[i]->executeTick();
        switch (status)
        {
            case BT::NodeStatus::FAILURE:   //失败就直接执行下一个子节点
                continue;
            case BT::NodeStatus::SUCCESS:
                ControlNode::haltChildren();
                return BT::NodeStatus::SUCCESS;
            case BT::NodeStatus::RUNNING:   //子节点不应该返回RUNNING
            default:
                std::stringstream error_msg;
                error_msg << "Invalid node status. Received status " << status << "from child "
                          << children_nodes_[i]->name();
                throw std::runtime_error(error_msg.str());
        }
    }
    // 说明全部节点都遍历过了但是没有成功的，返回FAILURE
    ControlNode::haltChildren();
    last_child_ticked_ = 0;   // reset
    return BT::NodeStatus::FAILURE;
}
}