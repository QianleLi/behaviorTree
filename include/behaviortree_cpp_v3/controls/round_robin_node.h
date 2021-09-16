/*
 * 来自NAV2的控制节点，已测试，运行正常
 */
#ifndef BEHAVIORTREE_CPP_V3_ROUND_ROBIN_NODE_H
#define BEHAVIORTREE_CPP_V3_ROUND_ROBIN_NODE_H
#include <string>

#include "behaviortree_cpp_v3/control_node.h"

namespace BT
{
class RoundRobinNode : public BT::ControlNode
{
  public:
    /**
     * @brief A constructor for nav2_behavior_tree::RoundRobinNode
     * @param name Name for the XML tag for this node
     */
    explicit RoundRobinNode(const std::string & name);

    /**
     * @brief A constructor for nav2_behavior_tree::RoundRobinNode
     * @param name Name for the XML tag for this node
     * @param config BT node configuration
     */
    RoundRobinNode(const std::string & name, const BT::NodeConfiguration & config);

    /**
     * @brief The main override required by a BT action
     * @return BT::NodeStatus Status of tick execution
     */
    BT::NodeStatus tick() override;

    /**
     * @brief The other (optional) override required by a BT action to reset node state
     */
    void halt() override;

    /**
     * @brief Creates list of BT ports
     * @return BT::PortsList Containing basic ports along with node-specific ports
     */
    static BT::PortsList providedPorts() {return {};}

  private:
    unsigned int current_child_idx_{0};
    unsigned int num_failed_children_{0};
};

}
#endif