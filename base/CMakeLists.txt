cmake_minimum_required(VERSION 3.8)

add_library(
    lc_base
    "list.c"
    "mem.c"
    "str.c"
    "vector.c"
)

add_executable(
    str_test
    "str_test.c"
)

target_link_libraries(
    str_test
    lc_base
)

add_executable(
    list_test
    "list_test.c"
)

target_link_libraries(
    list_test
    lc_base
)
