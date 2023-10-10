cmake_minimum_required(VERSION 3.20)

project(dynamic_ds C)

file(GLOB_RECURSE SRC_FILES
    src/*.c
)

# file(GLOB_RECURSE HDR_FILES
#     src/*h
# )

add_subdirectory(DStructs)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} DStructs)