//
// Created by Qianle Li on 2021/9/18.
//
#include "behaviortree_cpp_v3/bt_factory.h"

#include "dummy_nodes.h"
#include "movebase_node.h"
#include "behaviortree_cpp_v3/loggers/bt_cout_logger.h"
#include "behaviortree_cpp_v3/utils/enum.h"

using namespace BT;

BETTER_ENUM(TestType_, uint8_t, FIRST = 0, SECOND, THIRD);

namespace BT
{
template <>
inline TestType_ convertFromString(StringView str)
{
    printf("Converting string: \"%s\"\n", str.data());
    int temp = convertFromString<int>(str);
    switch (temp)
    {
        case 0:
            return TestType_::FIRST;
            break;
        case 1:
            return TestType_::SECOND;
            break;
        case 2:
            return TestType_::THIRD;
            break;
        default:
            break;
    }
    return TestType_::FIRST;
}
}   // end namespace BT

// clang-format off
static const char* xml_text = R"(

 <root main_tree_to_execute = "MainTree" >

     <BehaviorTree ID="MainTree">
        <Sequence name="root">
            <LeaveMyMessages     message="{message}" float_number="{float_number}" test_number="{test_number}"/>
            <SayTestSomething     message="{message}" float_number="{float_number}" test_number="{test_number}"/>
            <SayTestSomething     message="Message set from blackboard!!!" float_number="0.2f" test_number="2"/>
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
        setOutput("text", "The answer is 42");
        return BT::NodeStatus::SUCCESS;
    }

    // A node having ports MUST implement this STATIC method
    static BT::PortsList providedPorts()
    {
        return {BT::OutputPort<std::string>("text")};
    }
};

class LeaveMyMessages : public BT::SyncActionNode
{
  public:
    LeaveMyMessages(const std::string& name, const BT::NodeConfiguration& config)
      : BT::SyncActionNode(name, config)
    {
    }

    // You must override the virtual function tick()
    BT::NodeStatus tick() override
    {
        message = "This is the message I left!!!";
        setOutput("message", message);
        setOutput("float_number", float_number);
        setOutput("test_number", test_number);
        std::cout << "Someone left messages!!!" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    // It is mandatory to define this static method.
    static BT::PortsList providedPorts()
    {
        return {BT::OutputPort<std::string>("message"), BT::OutputPort<float>("float_number"),
                BT::OutputPort<TestType_>("test_number")};
    }

  private:
    std::string message;
    float float_number = 0.5f;
    TestType_ test_number = TestType_::SECOND;
};

class SayTestSomething : public BT::SyncActionNode
{
  public:
    SayTestSomething(const std::string& name, const BT::NodeConfiguration& config)
      : BT::SyncActionNode(name, config)
    {
    }

    // You must override the virtual function tick()
    BT::NodeStatus tick() override
    {
        auto msg1 = getInput<std::string>("message");
        std::cout << "Robot says: " << msg1.value() << std::endl;
        auto msg2 = getInput<float>("float_number");
        float float_number = msg2.value();
        std::cout << "The float number is " << float_number << "." << std::endl;
        TestType_ test_number = TestType_::FIRST;
        getInput("test_number", test_number);
        std::cout << "The int number is " << test_number << "." << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    // It is mandatory to define this static method.
    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<std::string>("message"), BT::InputPort<float>("float_number"),
                BT::InputPort<TestType_>("test_number")};
    }
};

int main()
{
    using namespace DummyNodes;

    BehaviorTreeFactory factory;
    factory.registerNodeType<LeaveMyMessages>("LeaveMyMessages");
    factory.registerNodeType<SayTestSomething>("SayTestSomething");
    factory.registerNodeType<SaySomething>("SaySomething");

    factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

    PortsList say_something_ports = {InputPort<std::string>("message")};
    factory.registerSimpleAction("SaySomething2", SaySomethingSimple, say_something_ports);

    auto tree = factory.createTreeFromText(xml_text);

    tree.tickRoot();

    return 0;
}
