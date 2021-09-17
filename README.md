This repository is based on BehaviorTree C++.           
The library is modified for our smart vacuum cleaner project and the boost lib was cross compiled for ARM achitecture cores.        

#### Steps for new nodes

1. Create new classes. In the mean time , think about new tags for those classes;  
2. List them in the CMakeLists.txt;
3. Include the header in behavior_tree.h;
4. Register them in bt_factory.cpp;
5. Make sure they work in the same way as they are designed.

 

