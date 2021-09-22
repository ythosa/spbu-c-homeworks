cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
        library/commonUtils/numericOperations.c
        library/commonUtils/arrayOperations.c
        )
add_library(library ${SOURCE_LIB})

add_executable(task_1.1 ./1.introduction/task_1.c)
add_executable(task_1.2 ./1.introduction/task_2.c)
target_link_libraries(task_1.2 library)
add_executable(task_1.3 ./1.introduction/task_3.c)
add_executable(task_1.4 ./1.introduction/task_4.c)
add_executable(task_1.5 ./1.introduction/task_5.c)
