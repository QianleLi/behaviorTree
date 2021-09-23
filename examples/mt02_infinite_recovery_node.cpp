//
// Created by Qianle Li on 2021/9/17.
//
// A test program to test infinite_recovery_node

#include "behaviortree_cpp_v3/bt_factory.h"
#include "dummy_nodes.h"
#include "behaviortree_cpp_v3/loggers/bt_cout_logger.h"
using namespace BT;
/*
static const char* xml_text = R"(

 <root main_tree_to_execute = "MainTree" >

     <BehaviorTree ID="MainTree">
        <RecoveryNode number_of_retries="6" name="root_sequence">
            <CheckBattery   name="battery_ok"/>
            <OpenGripper    name="open_gripper"/>
        </RecoveryNode>
     </BehaviorTree>

 </root>
 )";*/

static const char* xml_text = R"(

 <root main_tree_to_execute = "MainTree" >

     <BehaviorTree ID="MainTree">
        <InfiniteRecoveryNode name="root_sequence">
            <CheckBattery   name="battery_ok"/>
            <KeepRunningUntilSuccess>
                <OpenGripper    name="open_gripper"/>
            </KeepRunningUntilSuccess>
        </InfiniteRecoveryNode>
     </BehaviorTree>

 </root>
 )";

int main()
{
    BehaviorTreeFactory factory;

    using namespace DummyNodes;

    factory.registerSimpleCondition("CheckBattery", std::bind(CheckBatteryForceFail));

    GripperInterface gripper;
    factory.registerSimpleAction("OpenGripper", std::bind(&GripperInterface::open_after_retries, &gripper));

    auto tree = factory.createTreeFromText(xml_text);
    NodeStatus status = NodeStatus::RUNNING;
    StdCoutLogger logger_cout(tree);
    while(status == NodeStatus::RUNNING){
        std::cout << "attempt Once" << std::endl;
        status = tree.tickRoot();
        std::cout << "Sleep..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

    return 0;
}