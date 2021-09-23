//
// Created by Qianle Li on 2021/9/18.
//
#include "behaviortree_cpp_v3/bt_factory.h"

#include "dummy_nodes.h"
#include "movebase_node.h"
#include "behaviortree_cpp_v3/loggers/bt_cout_logger.h"

using namespace BT;
// clang-format off
static const char* xml_text = R"(

 <root main_tree_to_execute = "MainTree" >

     <BehaviorTree ID="MainTree">
        <Sequence name="root">
            <LeaveMessages     message="{message}" float_number="{float_number}" int_number="{int_number}"/>
            <SayLotsSomething     message="{message}" float_number="{float_number}" int_number="{int_number}"/>
            <SayLotsSomething     message="Message set from blackboard!!!" float_number="0.2f" int_number="3"/>
            <ThinkWhatToSay   text="{the_answer}"/>
            <SaySomething     message="{the_answer}" />
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
        setOutput("text", "The answer is 42" );
        return BT::NodeStatus::SUCCESS;
    }

    // A node having ports MUST implement this STATIC method
    static BT::PortsList providedPorts()
    {
        return { BT::OutputPort<std::string>("text") };
    }
};


int main()
{
    using namespace DummyNodes;

    BehaviorTreeFactory factory;
    factory.registerNodeType<LeaveMessages>("LeaveMessages");
    factory.registerNodeType<SayLotsSomething>("SayLotsSomething");
    factory.registerNodeType<SaySomething>("SaySomething");

    factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

    PortsList say_something_ports = { InputPort<std::string>("message") };
    factory.registerSimpleAction("SaySomething2", SaySomethingSimple, say_something_ports );

    auto tree = factory.createTreeFromText(xml_text);

    tree.tickRoot();

    return 0;
}

