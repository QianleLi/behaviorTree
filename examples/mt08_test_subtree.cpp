//
// Created by Qianle Li on 2022/2/18.
//
#include "behaviortree_cpp_v3/bt_factory.h"

#include "dummy_nodes.h"
#include "movebase_node.h"

using namespace BT;

class ThinkWhatToSay : public BT::SyncActionNode
{
  public:
    ThinkWhatToSay(const std::string& name, const BT::NodeConfiguration& config)
      : BT::SyncActionNode(name, config)
    {
    }

    // This Action simply write a value in the port "text"
    BT::NodeStatus tick() override
    {
        setOutput("text", "The answer is 42");

        std::string temp;

        return BT::NodeStatus::SUCCESS;
    }

    // A node having ports MUST implement this STATIC method
    static BT::PortsList providedPorts()
    {
        return {BT::OutputPort<std::string>("text"), BT::InputPort<std::string>("text")};
    }
};

class MySaySomething : public BT::SyncActionNode
{
  public:
    MySaySomething(const std::string& name, const BT::NodeConfiguration& config)
      : BT::SyncActionNode(name, config)
    {
    }

    // You must override the virtual function tick()
    BT::NodeStatus tick() override{
        auto msg = getInput<std::string>("text");
        if (!msg)
        {
            throw BT::RuntimeError( "missing required input [text]: ", msg.error() );
        }

        std::cout << "I says: " << msg.value() << std::endl;

        setOutput<std::string>("text", "The answer is 100");
        return BT::NodeStatus::SUCCESS;
    }

    // It is mandatory to define this static method.
    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<std::string>("text"), BT::OutputPort<std::string>("text")};
    }
};

int main()
{
    using namespace DummyNodes;

    BehaviorTreeFactory factory;

    factory.registerNodeType<SaySomething>("SaySomething");

    factory.registerNodeType<MySaySomething>("MySaySomething");

    factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

    PortsList say_something_ports = {InputPort<std::string>("message")};

    factory.registerSimpleAction("SaySomething2", SaySomethingSimple, say_something_ports);

    auto tree = factory.createTreeFromText(R"(./main_tree.xml)");

    tree.tickRoot();

    return 0;
}