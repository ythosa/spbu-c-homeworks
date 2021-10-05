cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
        library/commonUtils/numericOperations.c
        library/commonUtils/arrayOperations.c
        )
add_library(library ${SOURCE_LIB})

set(DATA_STRUCTURES_SOURCE_LIB lib/dataStructures/vector.c)
add_library(dataStructures ${DATA_STRUCTURES_SOURCE_LIB})
target_link_libraries(dataStructures m)

add_executable(task_1.1 ./1.introduction/task_1.c)
add_executable(task_1.2 ./1.introduction/task_2.c)
target_link_libraries(task_1.2 library)
add_executable(task_1.3 ./1.introduction/task_3.c)
add_executable(task_1.4 ./1.introduction/task_4.c)
add_executable(task_1.5 ./1.introduction/task_5.c)

add_executable(test1_task2 ./test1/task_2.c)
target_link_libraries(test1_task2 dataStructures)
