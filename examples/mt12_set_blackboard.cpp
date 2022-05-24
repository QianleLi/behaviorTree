//
// Created by Qianle Li on 2022/5/18.
//

#include <utility>

#include "behaviortree_cpp_v3/bt_factory.h"

#include "dummy_nodes.h"
#include "movebase_node.h"
#include "behaviortree_cpp_v3/loggers/bt_cout_logger.h"
#include "behaviortree_cpp_v3/utils/enum.h"

using namespace BT;

namespace BT
{
template <>
inline std::function<bool()> convertFromString(StringView str)
{
    printf("Converting string: \"%s\"\n", str.data());
    return nullptr;
}
}   // end namespace BT

// clang-format off
//<SetBlackboard output_key="function_ptr" value="nullptr"/>
static const char* xml_text = R"(

 <root main_tree_to_execute = "MainTree" >

     <BehaviorTree ID="MainTree">
        <Sequence name="root">
            <SetFunc ptr="{function_ptr}" />
<SetBlackboard output_key="function_ptr" value="nullptr"/>
            <UseFunc ptr="{function_ptr}" />
        </Sequence>
     </BehaviorTree>

 </root>
 )";
// clang-format on

class AddFunc : public BT::SyncActionNode
{
  public:
    AddFunc(const std::string& name, const BT::NodeConfiguration& config,
            std::function<bool()> func)
      : BT::SyncActionNode(name, config), func_(std::move(func))
    {
    }

    // This Action simply write a value in the port "text"
    BT::NodeStatus tick() override
    {
        setOutput("ptr", func_);
        return BT::NodeStatus::SUCCESS;
    }

    // A node having ports MUST implement this STATIC method
    static BT::PortsList providedPorts()
    {
        return {BT::OutputPort<std::function<bool()>>("ptr")};
    }

  private:
    std::function<bool()> func_;
};

class TestFunc : public BT::SyncActionNode
{
  public:
    TestFunc(const std::string& name, const BT::NodeConfiguration& config)
      : BT::SyncActionNode(name, config)
    {
    }

    // This Action simply write a value in the port "text"
    BT::NodeStatus tick() override
    {
        getInput("ptr", func_);
        if (!func_)
        {
            printf("No ptr");
            return BT::NodeStatus::FAILURE;
        }
        bool temp = func_();
        return BT::NodeStatus::SUCCESS;
    }

    // A node having ports MUST implement this STATIC method
    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<std::function<bool()>>("ptr")};
    }

  private:
    std::function<bool()> func_;
};

int main()
{
    using namespace DummyNodes;

    auto say_something = [=]() mutable {
        printf("la la la la la\n");
        return true;
    };

    BehaviorTreeFactory factory;
    auto builder_set_func = [say_something](const std::string &name, const BT::NodeConfiguration &config) {
        return std::make_unique<AddFunc>(name, config, say_something);
    };
    factory.registerBuilder<AddFunc>("SetFunc", builder_set_func);
    factory.registerNodeType<TestFunc>("UseFunc");

    auto tree = factory.createTreeFromText(xml_text);

    tree.tickRoot();

    return 0;
}
