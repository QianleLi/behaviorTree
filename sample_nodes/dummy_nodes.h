#ifndef SIMPLE_BT_NODES_H
#define SIMPLE_BT_NODES_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

namespace DummyNodes
{
BT::NodeStatus CheckBattery();
BT::NodeStatus CheckBatteryForceFail();

BT::NodeStatus CheckTemperature();
BT::NodeStatus SayHello();

class GripperInterface
{
  public:
    GripperInterface() : _opened(true)
    {
    }

    BT::NodeStatus open();
    BT::NodeStatus open_force_fail();
    BT::NodeStatus open_after_retries();

    BT::NodeStatus close();

  private:
    bool _opened;
    int try_cnt = 0;
};

//--------------------------------------

// Example of custom SyncActionNode (synchronous action)
// without ports.
class ApproachObject : public BT::SyncActionNode
{
  public:
    ApproachObject(const std::string& name) :
        BT::SyncActionNode(name, {})
    {
    }

    // You must override the virtual function tick()
    BT::NodeStatus tick() override;
};

// Example of custom SyncActionNode (synchronous action)
// with an input port.
class SaySomething : public BT::SyncActionNode
{
  public:
    SaySomething(const std::string& name, const BT::NodeConfiguration& config)
      : BT::SyncActionNode(name, config)
    {
    }

    // You must override the virtual function tick()
    BT::NodeStatus tick() override;

    // It is mandatory to define this static method.
    static BT::PortsList providedPorts()
    {
        return{ BT::InputPort<std::string>("message") };
    }
};

class LeaveMessages : public BT::SyncActionNode
{
  public:
    LeaveMessages(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config)
    {
    }

    // You must override the virtual function tick()
    BT::NodeStatus tick() override;

    // It is mandatory to define this static method.
    static BT::PortsList providedPorts()
    {
        return{ BT::OutputPort<std::string>("message"), BT::OutputPort<float>("float_number"),
                BT::OutputPort<int>("int_number") };
    }
  private:
    std::string message;
    float float_number = 0.5f;
    int int_number = 6;
};

class SayLotsSomething : public BT::SyncActionNode
{
  public:
    SayLotsSomething(const std::string& name, const BT::NodeConfiguration& config)
        : BT::SyncActionNode(name, config)
    {
    }

    // You must override the virtual function tick()
    BT::NodeStatus tick() override;

    // It is mandatory to define this static method.
    static BT::PortsList providedPorts()
    {
        return{ BT::InputPort<std::string>("message"), BT::InputPort<float>("float_number"),
            BT::InputPort<int>("int_number") };
    }
};

//Same as class SaySomething, but to be registered with SimpleActionNode
BT::NodeStatus SaySomethingSimple(BT::TreeNode& self);


inline void RegisterNodes(BT::BehaviorTreeFactory& factory)
{
    static GripperInterface grip_singleton;

    factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));
    factory.registerSimpleCondition("CheckTemperature", std::bind(CheckTemperature));
    factory.registerSimpleAction("SayHello", std::bind(SayHello));
    factory.registerSimpleAction("OpenGripper", std::bind(&GripperInterface::open, &grip_singleton));
    factory.registerSimpleAction("CloseGripper", std::bind(&GripperInterface::close, &grip_singleton));
    factory.registerNodeType<ApproachObject>("ApproachObject");
    factory.registerNodeType<SaySomething>("SaySomething");
    factory.registerNodeType<SayLotsSomething>("SayLotsSomething");
    factory.registerNodeType<LeaveMessages>("LeaveMessages");
}

} // end namespace

#endif   // SIMPLE_BT_NODES_H
