cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

add_library(commonUtils
        lib/commonUtils/numericOperations.c
        lib/commonUtils/arrayOperations.c
        )

set(DATA_STRUCTURES_SOURCE_LIB
        lib/dataStructures/string.c
        lib/dataStructures/list.c
        lib/dataStructures/dict.c
        lib/dataStructures/vector.c
        )
add_library(dataStructures ${DATA_STRUCTURES_SOURCE_LIB})
target_link_libraries(dataStructures m)

add_library(binary_lib lib/binary.c)
add_library(date lib/date/date.c)

add_library(io
        lib/io/csv.c
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
add_executable(task_3.2 ./3.pointers/task_2.c)
target_link_libraries(task_3.2 dataStructures)

add_executable(task_4.1 ./4.data_presentation/task_1.c)
target_link_libraries(task_4.1 binary_lib)
add_executable(task_4.2 ./4.data_presentation/task_2.c)
target_link_libraries(task_4.2 m)
add_executable(task_4.3 ./4.data_presentation/task_3.c)
target_link_libraries(task_4.3 binary_lib)

add_executable(test_1task_1 ./test1/task_1.c)
target_link_libraries(test_1task_1 dataStructures)
add_executable(test1_task2 ./test1/task_2.c)
target_link_libraries(test1_task2 dataStructures)

add_executable(test1_task3 ./test2/task_3.c)
target_link_libraries(test1_task3 date)
