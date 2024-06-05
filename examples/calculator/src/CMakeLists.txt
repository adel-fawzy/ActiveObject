cmake_minimum_required(VERSION 3.1)

project(Calculator LANGUAGES CXX)

find_package(Threads)                                                                                                                                                                      

add_executable(${PROJECT_NAME} main.cpp calculator.cpp)

target_link_libraries(${PROJECT_NAME}  ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(${PROJECT_NAME} PUBLIC "../../../include" PRIVATE "./include")
