#include "behaviortree_cpp_v3/bt_factory.h"

#include "dummy_nodes.h"
#include "movebase_node.h"
#include <thread>

using namespace BT;

/** This tutorial will teach you:
 *
 *  - The difference between Sequence and ReactiveSequence
 *
 *  - How to create an asynchronous ActionNode (an action that is execute in
 *    its own thread).
*/

// clang-format off

static const char* xml_text_sequence = R"(

 <root main_tree_to_execute = "MainTree" >

     <BehaviorTree ID="MainTree">
        <Sequence name="root">
            <BatteryOK/>
            <SaySomething   message="mission started..." />
            <MyAsyncMoveBase      goal="1;2;3"/>
            <SaySomething   message="mission completed!" />
        </Sequence>
     </BehaviorTree>

 </root>
 )";
// clang-format on

int main()
{
    using namespace DummyNodes;

    BehaviorTreeFactory factory;
    factory.registerSimpleCondition("BatteryOK", std::bind(CheckBattery));
    factory.registerNodeType<MyMoveBaseAction>("MyAsyncMoveBase");
    factory.registerNodeType<SaySomething>("SaySomething");

    // Compare the state transitions and messages using either
    // xml_text_sequence and xml_text_sequence_star

    // The main difference that you should notice is:
    //  1) When Sequence is used, BatteryOK is executed at __each__ tick()
    //  2) When SequenceStar is used, those ConditionNodes are executed only __once__.

    auto tree = factory.createTreeFromText(xml_text_sequence);

    while (tree.tickRoot() == BT::NodeStatus::RUNNING)
    {
        std::cout << "tick once " << std::this_thread::get_id() << std::endl;
        SleepMS(150);
    }

    std::cout << std::endl;
    return 0;
}

/*
 Expected output:

------------ BUILDING A NEW TREE ------------

--- 1st executeTick() ---
[ Battery: OK ]
Robot says: "mission started..."
[ MoveBase: STARTED ]. goal: x=1 y=2.0 theta=3.00

--- 2nd executeTick() ---
[ MoveBase: FINISHED ]

--- 3rd executeTick() ---
Robot says: "mission completed!"

------------ BUILDING A NEW TREE ------------

--- 1st executeTick() ---
[ Battery: OK ]
Robot says: "mission started..."
[ MoveBase: STARTED ]. goal: x=1 y=2.0 theta=3.00

--- 2nd executeTick() ---
[ Battery: OK ]
[ MoveBase: FINISHED ]

--- 3rd executeTick() ---
[ Battery: OK ]
Robot says: "mission completed!"

*/
