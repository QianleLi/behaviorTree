//
// Created by Qianle Li on 2022/2/15.
//
#include "behaviortree_cpp_v3/bt_factory.h"

#include "dummy_nodes.h"
#include "movebase_node.h"

using namespace BT;

/** This tutorial will teach you how basic input/output ports work.
 *
 * Ports are a mechanism to exchange information between Nodes using
 * a key/value storage called "Blackboard".
 * The type and number of ports of a Node is statically defined.
 *
 * Input Ports are like "argument" of a functions.
 * Output ports are, conceptually, like "return values".
 *
 * In this example, a Sequence of 5 Actions is executed:
 *
 *   - Actions 1 and 4 read the input "message" from a static string.
 *
 *   - Actions 3 and 5 read the input "message" from an entry in the
 *     blackboard called "the_answer".
 *
 *   - Action 2 writes something into the entry of the blackboard
 *     called "the_answer".
*/

// clang-format off
static const char* xml_text = R"(

 <root main_tree_to_execute = "MainTree" >

     <BehaviorTree ID="MainTree">
        <Sequence name="root">
            <SaySomething     message="start thinking..." />
            <ThinkWhatToSay   text="{the_answer}"/>
            <MySaySomething     text="{the_answer}" />
            <SaySomething2    message="SaySomething2 works too..." />
            <SaySomething2    message="{the_answer}" />
        </Sequence>
     </BehaviorTree>

 </root>
 )";
// clang-format on

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

        getInput("text", temp);
        printf("%s\n", temp.c_str());
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

    auto tree = factory.createTreeFromText(xml_text);

    tree.tickRoot();

    return 0;
}
