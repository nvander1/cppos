cmake_minimum_required(VERSION 3.1...3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_VERSION})
endif()

project(CppOS VERSION 0.0
              DESCRIPTION "Toy OS in C++"
              LANGUAGES CXX ASM-ATT)

add_subdirectory(os)
