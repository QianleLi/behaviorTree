//
// Created by Qianle Li on 2021/9/13.
//
/*
 * 本节点拥有fallback的特性，即有一个子节点返回SUCCCESS即结束；
 * 但是本节点每次被tick都从头来过，所有节点都从头开始，每一帧都遍历并tick所有子节点
 * 要求子节点只有SUCCESS和FAILURE两个状态
 * 已测试，运行正常
 */

#ifndef BEHAVIORTREE_CPP_V3_ONE_FRAME_FALLBACK_H
#define BEHAVIORTREE_CPP_V3_ONE_FRAME_FALLBACK_H

#include "behaviortree_cpp_v3/control_node.h"
namespace BT
{
    class OneFrameFallback : public BT::ControlNode
    {
    public:
        explicit OneFrameFallback(const std::string & name);

        OneFrameFallback(const std::string & name, const BT::NodeConfiguration & config);

        void halt() override;

        static BT::PortsList providedPorts() {return {};}

    protected:

        BT::NodeStatus tick() override;
    };

}
#endif