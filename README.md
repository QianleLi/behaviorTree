#  注意，如果在BV75项目里更新了本动态库，在上传到机器的时候一定要一同更新动态库，否则会发生无法找到动态库中函数实现的情况。

This repository is based on BehaviorTree C++.           
The library is modified for our smart vacuum cleaner project and the boost lib was cross compiled for ARM achitecture cores.        

#### Steps for new nodes

1. Create new classes. In the mean time , think about new tags for those classes;  
2. List them in the CMakeLists.txt;
3. Include the header in behavior_tree.h;
4. Register them in bt_factory.cpp;
5. Make sure they work in the same way as they are designed.





## BT设计原则

* 加入清晰明了的判断条件(Explicit Success Condition)来增加可读性，例如在解锁前检查锁的状态是否是锁住；在开门之前检查门是否已经被打开。通常将一个单纯的叶动作节点改成交由一个包括一个条件判断节点和一个行为节点的fallback节点。

* 利用隐含的队列(Implicit Sequence)来增加其反应性(reactivity)，通常用一个fallback节点实现，例如在人执行开门并通过等一系列动作之前检查人是否已经在门的另一边，如果第一个判断条件成功，即人已经无需开门，那么接下来的节点都不用逐一被tick。也就是在执行一系列动作之前先判断goal是否已经被达成。

* 利用决策树结构处理不同场景（废话）。

* 利用队列(Sequence)来确保安全性。有些时候机器人会产生不可逆的行为，因此利用队列使得机器人始终处于可控的范围内。例如机器人应该在每次执行任务之前检查电池电量，如果电量不足依然执行了任务，则无法完成任务产生无法预测的后果；在BT中加入队列，在执行主函数之前检查电量，如果电量不足，就不会进入主任务，从而阻止上述情况。

* 利用带有记忆的控制节点(Control Flow Nodes with Memory)来设计无反应性(non-reactive)的系统，控制节点带有记忆后会记录运行过程中子节点返回的状态直到该控制节点结束(SUCCESS or FAILURE)。带记忆的控制节点用于确保不会重复运行其子节点，而无反应系统适合用于场景完全可预测的环境，例如工厂中的机械臂，抓取、移动、放置，同时在移动的过程中机械手都会抓紧物体，每次运行不会重复tick任何一个节点，同样不能处理任何其他突发情况。

* 为BT选择合适的粒度(Granularity)。确定BT的粒度即明确行为树与每一个叶节点的作用范围。通常考虑以下两点：

  * 只有当几个小动作经常被以特定的组合执行才将它们作为一个动作封装进叶节点中；
  * 只有当BT的某些部分可能被别的BT复用或者用来增加反应性的时候才将该BT打破成节点或者子树。

  比如对于一个人形机器人来说，sit和stand是常用动作且无法被继续拆分；而对于机械臂来说，将抓取、移动、放置物体分成三个节点能更好的分别应对突发事件。



## BV75 BT常用节点

#### Sequence

类似于逻辑运算与。子节点依次执行，只要有一个节点失败，整个控制队列失败；所有子节点成功则整个控制队列成功。在运行过程中只有子节点返回RUNNING才会暂停，下一次继续tick该RUNNING节点。如果所有节点只返回SUCCESS or FAILURE，那么Sequence一帧即可执行完毕。

#### Fallback/Selector

类似于逻辑运算或。子节点依次执行，只要一个节点成功，整个Fallback成功；所有子节点失败则整个Fallback失败。可以利用子节点的先后顺序来优先执行更高优先级的方法。在运行过程中只有子节点返回RUNNING才会暂停，下一次继续tick该RUNNING节点。如果所有节点只返回SUCCESS or FAILURE，那么Fallback一帧即可执行完毕。

 
