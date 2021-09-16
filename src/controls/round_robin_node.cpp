// Copyright (c) 2019 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>

#include "behaviortree_cpp_v3/controls/round_robin_node.h"

namespace BT
{

RoundRobinNode::RoundRobinNode(const std::string & name)
    : BT::ControlNode::ControlNode(name, {})
{
    setRegistrationID("RoundRobin");
}

RoundRobinNode::RoundRobinNode(
    const std::string & name,
    const BT::NodeConfiguration & config)
    : BT::ControlNode(name, config)
{
}

BT::NodeStatus RoundRobinNode::tick()
{
    const auto num_children = children_nodes_.size();

    setStatus(BT::NodeStatus::RUNNING);

    while (num_failed_children_ < num_children) {    //除非所有节点都失败才退出
        TreeNode * child_node = children_nodes_[current_child_idx_];
        const BT::NodeStatus child_status = child_node->executeTick();

        switch (child_status) {
            case BT::NodeStatus::SUCCESS:
            {
                if (++current_child_idx_ >= num_children) {   //执行完最后一个节点再回到第一个节点
                    current_child_idx_ = 0;
                }
                num_failed_children_ = 0;
                ControlNode::haltChildren();
                return BT::NodeStatus::SUCCESS;
            }

            case BT::NodeStatus::FAILURE:   //遇到失败则tick下一个节点
            {
                if (++current_child_idx_ >= num_children) {    //执行完最后一个节点再回到第一个节点
                    current_child_idx_ = 0;
                }
                num_failed_children_++;
                break;
            }

            case BT::NodeStatus::RUNNING:
            {
                return BT::NodeStatus::RUNNING;
            }

            default:
            {
                throw BT::LogicError("Invalid status return from BT node");
            }
        }
    }

    halt();
    return BT::NodeStatus::FAILURE;
}

void RoundRobinNode::halt()
{
    ControlNode::halt();
    current_child_idx_ = 0;
    num_failed_children_ = 0;
}

}
/*
#include <behaviortree_cpp_v3/bt_factory.h>
BT_REGISTER_NODES(factory)
    {
        factory.registerNodeType<BT::RoundRobinNode>("RoundRobin");
    }
*/