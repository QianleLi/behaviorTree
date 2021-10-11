//
// Created by Qianle Li on 2021/10/9.
//
#include "behaviortree_cpp_v3/bt_factory.h"

using namespace BT;

/* This tutorial will teach you how to deal with ports when its
 *  type is not std::string.
*/

// We want to be able to use this custom type
struct Position2D
{
    double x, y;
};
using Path = std::vector<Position2D>;

namespace BT
{
template <>
inline Position2D convertFromString(StringView str)
{
    printf("Converting string: \"%s\"\n", str.data());

    // real numbers separated by semicolons
    auto parts = splitString(str, ';');
    if (parts.size() != 2)
    {
        throw RuntimeError("invalid input)");
    }
    else
    {
        Position2D output;
        output.x = convertFromString<double>(parts[0]);
        output.y = convertFromString<double>(parts[1]);
        return output;
    }
}
}   // namespace BT

class SetPath : public SyncActionNode
{
  public:
    SetPath(const std::string& name, const NodeConfiguration& config) : SyncActionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        Position2D mypoint1 = {1.1, 2.3};
        Position2D mypoint2 = {2, 9};
        Position2D mypoint3 = {100, -200};
        Path mypath = {mypoint1, mypoint2, mypoint3};
        setOutput("path", mypath);
        return NodeStatus::SUCCESS;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<Path>("path")};
    }
};

//TODO continue-------------------
class PrintPath : public SyncActionNode
{
  public:
    PrintPath(const std::string& name, const NodeConfiguration& config)
      : SyncActionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        auto res = getInput<Path>("path");
        if (!res)
        {
            throw RuntimeError("error reading port [path]:", res.error());
        }
        Path path = res.value();
        for (auto& point : path)
        {
            printf("Target positions: [ %.1f, %.1f ]\n", point.x, point.y);
        }

        return NodeStatus::SUCCESS;
    }

    static PortsList providedPorts()
    {
        return {InputPort<Path>("path")};
    }
};

// clang-format off
static const char* xml_text = R"(

 <root main_tree_to_execute = "MainTree" >
     <BehaviorTree ID="MainTree">
        <Sequence name="root">
            <SetPath   path="{Path}" />
            <PrintPath     path="{Path}" />
        </Sequence>
     </BehaviorTree>
 </root>
 )";

int main()
{
    using namespace BT;

    BehaviorTreeFactory factory;
    factory.registerNodeType<SetPath>("SetPath");
    factory.registerNodeType<PrintPath>("PrintPath");

    auto tree = factory.createTreeFromText(xml_text);
    tree.tickRoot();

    return 0;
}