cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
        library/commonUtils/numericOperations.c
        library/commonUtils/arrayOperations.c
        )
add_library(library ${SOURCE_LIB})

add_executable(task_2 ./1.introduction/task_2.c)
target_link_libraries(task_2 library)
