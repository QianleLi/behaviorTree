//
// Created by Qianle Li on 2021/9/17.
//
// A test program to test one_frame_sequence

#include "behaviortree_cpp_v3/bt_factory.h"
#include "dummy_nodes.h"
#include "behaviortree_cpp_v3/loggers/bt_cout_logger.h"
using namespace BT;

static const char* xml_text = R"(

 <root main_tree_to_execute = "MainTree" >

     <BehaviorTree ID="MainTree">
        <OneFrameSequence name="root_sequence">
            <CheckBattery   name="battery_ok"/>
            <OpenGripper    name="open_gripper"/>
            <ForceFailure>
                <ApproachObject name="approach_object"/>
            </ForceFailure>
            <CloseGripper   name="close_gripper"/>
        </OneFrameSequence>
     </BehaviorTree>

 </root>
 )";

int main()
{
    BehaviorTreeFactory factory;

    using namespace DummyNodes;

    factory.registerNodeType<ApproachObject>("ApproachObject");

    factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));

    GripperInterface gripper;
    factory.registerSimpleAction("OpenGripper", std::bind(&GripperInterface::open, &gripper));
    factory.registerSimpleAction("CloseGripper", std::bind(&GripperInterface::close, &gripper));

    auto tree = factory.createTreeFromText(xml_text);
    StdCoutLogger logger_cout(tree);
    std::cout << "attempt 1" << std::endl;
    tree.tickRoot();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "attempt 2" << std::endl;
    tree.tickRoot();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "attempt 3" << std::endl;
    tree.tickRoot();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "attempt 4" << std::endl;
    tree.tickRoot();

    return 0;
}