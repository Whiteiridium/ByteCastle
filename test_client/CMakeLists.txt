cmake_minimum_required(VERSION 3.10)
project(NetworkClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(NetworkClient test_client.cpp)

target_include_directories(NetworkClient PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(NetworkClient PRIVATE ${Boost_LIBRARIES})
