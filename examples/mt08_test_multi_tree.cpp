//
// Created by Qianle Li on 2022/2/22.
//

#include "behaviortree_cpp_v3/bt_factory.h"
#include "dummy_nodes.h"
#include "behaviortree_cpp_v3/loggers/bt_cout_logger.h"

using namespace BT;

class HearWhisper : public BT::SyncActionNode
{
  public:
    HearWhisper(const std::string& name, const BT::NodeConfiguration& config)
      : BT::SyncActionNode(name, config)
    {
    }

    BT::NodeStatus tick() override
    {
        std::string temp;
        getInput("text", temp);
        printf("I heard '%s'. I agree.\n", temp.c_str());
        return BT::NodeStatus::SUCCESS;
    }

    // A node having ports MUST implement this STATIC method
    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<std::string>("text")};
    }
};

class WhisperSomething : public BT::SyncActionNode
{
  public:
    WhisperSomething(const std::string& name, const BT::NodeConfiguration& config)
      : BT::SyncActionNode(name, config)
    {
    }

    BT::NodeStatus tick() override
    {
        std::string temp;

        getInput("words", temp);

        printf("I whisper...\n");
        setOutput<std::string>("text", temp);
        return BT::NodeStatus::SUCCESS;
    }

    static BT::PortsList providedPorts()
    {
        return {BT::OutputPort<std::string>("text"), BT::InputPort<std::string>("words")};
    }
};

static const char* xml_text1 = R"(

 <root main_tree_to_execute = "MainTree1" >

     <BehaviorTree ID="MainTree1">
        <Sequence name="root">
            <WhisperSomething  text="{something}" words="I love BT!"/>
            <HearWhisper  text="{something}" />
        </Sequence>
     </BehaviorTree>

 </root>
 )";

static const char* xml_text2 = R"(

 <root main_tree_to_execute = "MainTree2" >

     <BehaviorTree ID="MainTree2">
        <Sequence name="root_sequence">
            <CheckBattery   name="battery_ok" />
            <WhisperSomething  text="{something}" words="F**k BT!"/>
            <HearWhisper  text="{something}" />
        </Sequence>
     </BehaviorTree>

 </root>
 )";

int main()
{
    using namespace DummyNodes;

    BehaviorTreeFactory factory;

    factory.registerNodeType<WhisperSomething>("WhisperSomething");
    factory.registerNodeType<HearWhisper>("HearWhisper");

    factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));

    auto tree1 = factory.createTreeFromText(xml_text1);

    NodeStatus status = NodeStatus::RUNNING;

    while (status != NodeStatus::SUCCESS)
    {
        printf("tick tree1 Once\n");
        status = tree1.tickRoot();
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    auto tree2 = factory.createTreeFromText(xml_text2);
//    StdCoutLogger logger_cout(tree2);
    status = NodeStatus::RUNNING;
    while (status != NodeStatus::SUCCESS)
    {
        printf("tick tree2 Once\n");
        status = tree2.tickRoot();
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

    return 0;
}