//
// Created by Qianle Li on 2022/2/10.
//

#include "behaviortree_cpp_v3/decorators/retry_until_successful.h"

namespace BT
{
RetryUntilSuccessful::RetryUntilSuccessful(const std::string& name)
  : DecoratorNode(name, {})
{
    setRegistrationID("RetryUntilSuccessful");
}

void RetryUntilSuccessful::halt()
{
    DecoratorNode::halt();
}

NodeStatus RetryUntilSuccessful::tick()
{
    setStatus(NodeStatus::RUNNING);

    while (true)
    {
        NodeStatus child_state = child_node_->executeTick();
        switch (child_state)
        {
            case NodeStatus::SUCCESS: {
                haltChild();
                return NodeStatus::SUCCESS;
            }

            case NodeStatus::FAILURE:
            case NodeStatus::RUNNING: {
                return NodeStatus::RUNNING;
                break;
            }

            default: {
                printf("A child node must never return IDLE\n");
                break;
            }
        }
    }

    return NodeStatus::FAILURE;
}

}   // namespace BT