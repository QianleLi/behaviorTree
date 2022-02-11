//
// Created by Qianle Li on 2022/2/10.
//

#ifndef BEHAVIORTREE_CPP_V3_RETRY_UNTIL_SUCCESS_H
#define BEHAVIORTREE_CPP_V3_RETRY_UNTIL_SUCCESS_H

#include "behaviortree_cpp_v3/decorator_node.h"

namespace BT
{
class RetryUntilSuccessful : public DecoratorNode
{
  public:
    RetryUntilSuccessful(const std::string& name);

    virtual ~RetryUntilSuccessful() override = default;

    virtual void halt() override;

  private:
    virtual BT::NodeStatus tick() override;
};
}   // namespace BT

#endif   //BEHAVIORTREE_CPP_V3_RETRY_UNTIL_SUCCESS_H
