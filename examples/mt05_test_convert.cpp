//
// Created by Qianle Li on 2021/10/9.
//
#include "behaviortree_cpp_v3/bt_factory.h"
#include "behaviortree_cpp_v3/BT_common.h"

using namespace BT;

/* This tutorial will teach you how to deal with ports when its
 *  type is not std::string.
*/
using Path = std::vector<Point_2f>;
using rcpp = std::vector<std::pair<Path, Path>>;

class SetPath : public SyncActionNode
{
  public:
    SetPath(const std::string& name, const NodeConfiguration& config) : SyncActionNode(name, config)
    {
    }

    NodeStatus tick() override
    {
        Point_2f mypoint1 = {1.1, 2.3};
        Point_2f mypoint2 = {1.1, 2.3};
        Point_2f mypoint3 = {1.1, 2.3};
        Point_2f mypoint4 = {2, 9};
        Point_2f mypoint5 = {2, 9};
        Point_2f mypoint6 = {2, 9};
        Path mypath = {mypoint1, mypoint2, mypoint3};
        Path mypath2 = {mypoint4, mypoint5, mypoint6};
        rcpp fold_path;
        fold_path.push_back(std::make_pair(mypath2, std::vector<Point_2f>()));
        TaskType_ task_type = BT::NOPASS;
        setOutput("path", mypath);
        setOutput("taskType", task_type);
        setOutput("foldPath", fold_path);
        return NodeStatus::SUCCESS;
    }
    static PortsList providedPorts()
    {
        return {OutputPort<Path>("path"), OutputPort<TaskType_>("taskType"),
                OutputPort<rcpp>("foldPath")};
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
        auto res2 = getInput<BT::TaskType_>("taskType");
        auto res3 = getInput<rcpp>("foldPath");
        auto task_type = res2.value();
        if (!res)
        {
            throw RuntimeError("error reading port [path]:", res.error());
        }
        Path path = res.value();
        for (auto& point : path)
        {
            printf("Target positions: [ %.1f, %.1f ]\n", point.x, point.y);
        }
        std::cout << "Task type: " << task_type << std::endl;

        rcpp fold_paths = res3.value();
        Path fold_path = fold_paths.begin()->first;
        for (auto& point : fold_path)
        {
            printf("Target positions: [ %.1f, %.1f ]\n", point.x, point.y);
        }

        return NodeStatus::SUCCESS;
    }

    static PortsList providedPorts()
    {
        return {InputPort<Path>("path"), InputPort<TaskType_>("taskType"),
                InputPort<rcpp>("foldPath")};
    }
};

// clang-format off
static const char* xml_text = R"(

 <root main_tree_to_execute = "MainTree" >
     <BehaviorTree ID="MainTree">
        <Sequence name="root">
            <SetPath   path="{Path}" taskType="{TaskType}" foldPath = "{FoldPath}"/>
            <PrintPath     path="{Path}"  taskType="{TaskType}" foldPath = "{FoldPath}"/>
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