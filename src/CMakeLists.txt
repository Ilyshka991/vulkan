cmake_minimum_required(VERSION 3.10)

add_executable(${PROJECT_NAME}
        hello_triangle.h hello_triangle.cpp
        main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC framework)