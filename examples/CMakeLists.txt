cmake_minimum_required(VERSION 3.5.1)

include_directories(../sample_nodes)

set(CMAKE_DEBUG_POSTFIX "")

# The plugin libdummy_nodes.so can be linked statically or
# loaded dynamically at run-time.
add_executable(t01_first_tree_static t01_build_your_first_tree.cpp)
target_compile_definitions(t01_first_tree_static PRIVATE "MANUAL_STATIC_LINKING")
target_link_libraries(t01_first_tree_static ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes ${COROUTINE_LIBS})

add_executable(t01_first_tree_dynamic t01_build_your_first_tree.cpp)
target_link_libraries(t01_first_tree_dynamic ${BEHAVIOR_TREE_LIBRARY})


add_executable(t02_basic_ports t02_basic_ports.cpp)
target_link_libraries(t02_basic_ports ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes ${COROUTINE_LIBS})

add_executable(t03_generic_ports t03_generic_ports.cpp)
target_link_libraries(t03_generic_ports ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes ${COROUTINE_LIBS})

add_executable(t04_reactive_sequence t04_reactive_sequence.cpp)
target_link_libraries(t04_reactive_sequence ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes ${COROUTINE_LIBS})

add_executable(t05_cross_door t05_crossdoor.cpp)
target_link_libraries(t05_cross_door ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes ${COROUTINE_LIBS})

add_executable(t06_subtree_port_remapping t06_subtree_port_remapping.cpp)
target_link_libraries(t06_subtree_port_remapping ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes ${COROUTINE_LIBS})

add_executable(t07_wrap_legacy t07_wrap_legacy.cpp)
target_link_libraries(t07_wrap_legacy ${BEHAVIOR_TREE_LIBRARY} ${COROUTINE_LIBS})

add_executable(t08_additional_node_args t08_additional_node_args.cpp)
target_link_libraries(t08_additional_node_args ${BEHAVIOR_TREE_LIBRARY} ${COROUTINE_LIBS})

if (BT_COROUTINES)
    add_executable(t09_async_actions_coroutines t09_async_actions_coroutines.cpp)
    target_link_libraries(t09_async_actions_coroutines ${BEHAVIOR_TREE_LIBRARY} ${COROUTINE_LIBS})
endif ()

add_executable(t10_include_trees t10_include_trees.cpp)
target_link_libraries(t10_include_trees ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes ${COROUTINE_LIBS})


add_executable(t11_runtime_ports t11_runtime_ports.cpp)
target_link_libraries(t11_runtime_ports ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes ${COROUTINE_LIBS})

if (CURSES_FOUND)
    add_executable(t12_ncurses_manual_selector t12_ncurses_manual_selector.cpp)
    target_link_libraries(t12_ncurses_manual_selector ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes)
endif ()

add_executable(mt02_infinite_recovery_node mt02_infinite_recovery_node.cpp)
target_link_libraries(mt02_infinite_recovery_node ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes)

add_executable(mt04_test_blackboard mt04_test_blackboard.cpp)
target_link_libraries(mt04_test_blackboard ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes)

add_executable(mt05_test_convert mt05_test_convert.cpp)
target_link_libraries(mt05_test_convert ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes)

add_executable(mt06_retry_until_successful mt06_retry_until_successful.cpp)
target_link_libraries(mt06_retry_until_successful ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes)

add_executable(mt07_test_output_and_input mt07_test_output_and_input.cpp)
target_link_libraries(mt07_test_output_and_input ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes)

add_executable(mt08_test_multi_tree mt08_test_multi_tree.cpp)
target_link_libraries(mt08_test_multi_tree ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes)

add_executable(mt09_test_sub_tree mt09_test_sub_tree.cpp)
target_link_libraries(mt09_test_sub_tree ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes)

add_executable(mt10_test_find_node mt10_test_find_node.cpp)
target_link_libraries(mt10_test_find_node ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes)

add_executable(mt11_test_async mt11_test_async.cpp)
target_link_libraries(mt11_test_async ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes)

add_executable(mt12_set_blackboard mt12_set_blackboard.cpp)
target_link_libraries(mt12_set_blackboard ${BEHAVIOR_TREE_LIBRARY} bt_sample_nodes)