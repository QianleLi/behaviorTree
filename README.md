#  注意，如果在BV75项目里更新了本动态库，在上传到机器的时候一定要一同更新动态库，否则会发生无法找到动态库中函数实现的情况。

This repository is based on BehaviorTree C++.           
The library is modified for our smart vacuum cleaner project and the boost lib was cross compiled for ARM achitecture cores.        

#### Steps for new nodes

1. Create new classes. In the mean time , think about new tags for those classes;  
2. List them in the CMakeLists.txt;
3. Include the header in behavior_tree.h;
4. Register them in bt_factory.cpp;
5. Make sure they work in the same way as they are designed.

 

