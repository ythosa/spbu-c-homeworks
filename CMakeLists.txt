cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
        library/commonUtils/numericOperations.c
        library/commonUtils/arrayOperations.c library/commonUtils/arrayOperations.h)
add_library(library ${SOURCE_LIB})

set(SOURCE
        1.introduction/task_2.c
        )

add_executable(spbu_c_homeworks ${SOURCE})
target_link_libraries(spbu_c_homeworks library)
