//
// Created by Qianle Li on 2021/9/17.
//

/*
 * 本节点拥有sequence的特性，即必须顺序执行所有的子节点，且必须执行成功；
 * 但是本节点每次被tick都从头来过，所有节点都从头开始，每一帧都遍历并tick所有子节点
 * 要求子节点只有SUCCESS和FAILURE两个状态
 * 已测试通过
 */

#ifndef BEHAVIORTREE_CPP_V3_ONE_FRAME_SEQUENCE_H
#define BEHAVIORTREE_CPP_V3_ONE_FRAME_SEQUENCE_H

#include "behaviortree_cpp_v3/control_node.h"

namespace BT
{
class OneFrameSequence : public BT::ControlNode
{
  public:
    explicit OneFrameSequence(const std::string & name);

    OneFrameSequence(const std::string & name, const BT::NodeConfiguration & config);

    void halt() override;

    static BT::PortsList providedPorts() {return {};}

  protected:

    BT::NodeStatus tick() override;
};

}

#endif   //BEHAVIORTREE_CPP_V3_ONE_FRAME_SEQUENCE_H
