cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

add_library(commonUtils
        library/commonUtils/numericOperations.c
        library/commonUtils/arrayOperations.c
        )

add_library(dataStructures
        library/dataStructures/string.c
        library/dataStructures/list.c
        library/dataStructures/dict.c
        )

add_library(io
        library/io/csv.c
        )

add_executable(task_1.1 ./1.introduction/task_1.c)
add_executable(task_1.2 ./1.introduction/task_2.c)
target_link_libraries(task_1.2 commonUtils)
add_executable(task_1.3 ./1.introduction/task_3.c)
add_executable(task_1.4 ./1.introduction/task_4.c)
add_executable(task_1.5 ./1.introduction/task_5.c)

add_executable(task_3.1 ./3.pointers/task_1.c)
target_link_libraries(task_3.1 dataStructures)
target_link_libraries(task_3.1 io)
