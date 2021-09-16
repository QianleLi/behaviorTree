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

#include <stdexcept>
#include <sstream>
#include <string>

#include "behaviortree_cpp_v3/controls/pipeline_sequence.h"

namespace BT
{

PipelineSequence::PipelineSequence(const std::string & name)
    : BT::ControlNode(name, {})
{
    setRegistrationID("PipelineSequence");
}

PipelineSequence::PipelineSequence(
    const std::string & name,
    const BT::NodeConfiguration & config)
    : BT::ControlNode(name, config)
{
}

BT::NodeStatus PipelineSequence::tick()
{
    // 每一帧逐一tick所有子节点，如果子节点没有RUNNING状态，那么就会tick所有的节点，除非有节点返回了FAILURE
    for (std::size_t i = 0; i < children_nodes_.size(); ++i) {
        auto status = children_nodes_[i]->executeTick();
        switch (status) {
            case BT::NodeStatus::FAILURE:  //只要有一个子节点返回FAILURE，pipeline也返回FAILURE
                ControlNode::haltChildren();
                last_child_ticked_ = 0;  // reset
                return status;
            case BT::NodeStatus::SUCCESS:  //返回成功，什么也不做，下一帧再从第一个节点开始tick
                // do nothing and continue on to the next child. If it is the last child
                // we'll exit the loop and hit the wrap-up code at the end of the method.
                break;
            case BT::NodeStatus::RUNNING:  //返回成功，什么也不做，下一帧再从第一个节点开始tick
                if (i >= last_child_ticked_) {   //tick到之前没运行过的节点直接返回，不继续tick后面的节点
                    last_child_ticked_ = i;
                    return status;
                }
                // else do nothing and continue on to the next child
                break;
            default:
                std::stringstream error_msg;
                error_msg << "Invalid node status. Received status " << status <<
                          "from child " << children_nodes_[i]->name();
                throw std::runtime_error(error_msg.str());
        }
    }
    // 到这里说明最后一个节点返回了SUCCESS，结束并返回SUCCESS
    ControlNode::haltChildren();
    last_child_ticked_ = 0;  // reset
    return BT::NodeStatus::SUCCESS;
}

void PipelineSequence::halt()
{
    BT::ControlNode::halt();
    last_child_ticked_ = 0;
}

}
/*
#include <behaviortree_cpp_v3/bt_factory.h>
BT_REGISTER_NODES(factory)
    {
        factory.registerNodeType<BT::PipelineSequence>("PipelineSequence");
    }
*/