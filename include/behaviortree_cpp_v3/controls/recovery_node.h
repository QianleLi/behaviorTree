/*
 * 来自NAV2的控制节点，已测试，运行正常
 */
/*
 * 第一个节点失败后运行第二个节点，第二个节点失败后整个recovery失败，如果第二个节点成功，再运行第一个节点，视为一次retry；
 * 在建立recovery节点的时候就设置retry的最大次数，超过次数第一个节点依然无法成功整个recovery失败。
 * 整个recovery节点在一阵之内完成
 */
#ifndef BEHAVIORTREE_CPP_V3_RECOVERY_NODE_H
#define BEHAVIORTREE_CPP_V3_RECOVERY_NODE_H
#include <string>
#include "behaviortree_cpp_v3/control_node.h"

namespace BT
{
/**
 * @brief The RecoveryNode has only two children and returns SUCCESS if and only if the first child
 * returns SUCCESS.
 *
 * - If the first child returns FAILURE, the second child will be executed.  After that the first
 * child is executed again if the second child returns SUCCESS.
 *
 * - If the first or second child returns RUNNING, this node returns RUNNING.
 *
 * - If the second child returns FAILURE, this control node will stop the loop and returns FAILURE.
 *
 */
class RecoveryNode : public BT::ControlNode
{
  public:
    /**
     * @brief A constructor for nav2_behavior_tree::RecoveryNode
     * @param name Name for the XML tag for this node
     * @param conf BT node configuration
     */
    RecoveryNode(
        const std::string & name,
        const BT::NodeConfiguration & conf);

    /**
     * @brief A destructor for nav2_behavior_tree::RecoveryNode
     */
    ~RecoveryNode() override = default;

    /**
     * @brief Creates list of BT ports
     * @return BT::PortsList Containing basic ports along with node-specific ports
     */
    static BT::PortsList providedPorts()
    {
        return {
            BT::InputPort<int>("number_of_retries", 1, "Number of retries")
        };
    }

  private:
    unsigned int current_child_idx_;
    unsigned int number_of_retries_;
    unsigned int retry_count_;

    /**
     * @brief The main override required by a BT action
     * @return BT::NodeStatus Status of tick execution
     */
    BT::NodeStatus tick() override;

    /**
     * @brief The other (optional) override required by a BT action to reset node state
     */
    void halt() override;
};

}
#endif