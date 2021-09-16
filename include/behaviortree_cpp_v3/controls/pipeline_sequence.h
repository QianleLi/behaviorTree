#ifndef BEHAVIORTREE_CPP_V3_PIPELINE_SEQUENCE_H
#define BEHAVIORTREE_CPP_V3_PIPELINE_SEQUENCE_H

#include <string>
#include "behaviortree_cpp_v3/control_node.h"

namespace BT
{
class PipelineSequence : public BT::ControlNode
{
  public:
    /**
     * @brief A constructor for nav2_behavior_tree::PipelineSequence
     * @param name Name for the XML tag for this node
     */
    explicit PipelineSequence(const std::string & name);

    /**
     * @brief A constructor for nav2_behavior_tree::PipelineSequence
     * @param name Name for the XML tag for this node
     * @param config BT node configuration
     */
    PipelineSequence(const std::string & name, const BT::NodeConfiguration & config);

    /**
     * @brief The other (optional) override required by a BT action to reset node state
     */
    void halt() override;

    /**
     * @brief Creates list of BT ports
     * @return BT::PortsList Containing basic ports along with node-specific ports
     */
    static BT::PortsList providedPorts() {return {};}

  protected:
    /**
     * @brief The main override required by a BT action
     * @return BT::NodeStatus Status of tick execution
     */
    BT::NodeStatus tick() override;

    std::size_t last_child_ticked_ = 0;
};

}
#endif