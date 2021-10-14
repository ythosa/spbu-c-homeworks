cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

add_library(commonUtils
        lib/commonUtils/numericOperations.c
        lib/commonUtils/arrayOperations.c
        )

add_library(dataStructures
        lib/dataStructures/string.c
        lib/dataStructures/list.c
        lib/dataStructures/dict.c
        )

add_library(io
        lib/io/csv.c
        )

set(DATA_STRUCTURES_SOURCE_LIB lib/dataStructures/vector.c)
add_library(dataStructures ${DATA_STRUCTURES_SOURCE_LIB})
target_link_libraries(dataStructures m)

add_executable(task_1.1 ./1.introduction/task_1.c)
add_executable(task_1.2 ./1.introduction/task_2.c)
target_link_libraries(task_1.2 commonUtils)
add_executable(task_1.3 ./1.introduction/task_3.c)
add_executable(task_1.4 ./1.introduction/task_4.c)
add_executable(task_1.5 ./1.introduction/task_5.c)


add_executable(task_3.1 ./3.pointers/task_1.c)
target_link_libraries(task_3.1 dataStructures)
target_link_libraries(task_3.1 io)
add_executable(task_3.2 ./3.pointers/task_2.c)
target_link_libraries(task_3.2 dataStructures)

add_executable(test_1task_1 ./test1/task_1.c)
target_link_libraries(test_1task_1 dataStructures)

add_executable(test1_task2 ./test1/task_2.c)
target_link_libraries(test1_task2 dataStructures)


