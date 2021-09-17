//
// Created by Qianle Li on 2021/9/17.
//

#include "behaviortree_cpp_v3/controls/one_frame_sequence.h"

namespace BT
{

OneFrameSequence::OneFrameSequence(const std::string & name)
    : BT::ControlNode(name, {})
{
    setRegistrationID("OneFrameSequence");
}

OneFrameSequence::OneFrameSequence(
    const std::string & name,
    const BT::NodeConfiguration & config)
    : BT::ControlNode(name, config)
{
    setRegistrationID("OneFrameSequence");
}

BT::NodeStatus OneFrameSequence::tick()
{
    setStatus(BT::NodeStatus::RUNNING);
    // 每一帧都要执行所有的子节点，要求子节点要么返回SUCCESS要么返回FAILURE
    for (auto & children_node : children_nodes_)
    {
        auto status = children_node->executeTick();
        switch (status)
        {
            case BT::NodeStatus::FAILURE:   //失败即sequence整个失败
                return BT::NodeStatus::FAILURE;
            case BT::NodeStatus::SUCCESS:    //一个节点成功，继续
                continue;
            case BT::NodeStatus::RUNNING:   //子节点不应该返回RUNNING
            default:
                std::stringstream error_msg;
                error_msg << "Invalid node status. Received status " << status << "from child "
                          << children_node->name();
                throw std::runtime_error(error_msg.str());
        }
    }
    // 说明全部节点都遍历过了且均成功，返回成功
    ControlNode::haltChildren();
    return BT::NodeStatus::SUCCESS;
}

void OneFrameSequence::halt()
{
    BT::ControlNode::halt();
}

}