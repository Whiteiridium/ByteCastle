cmake_minimum_required(VERSION 3.10)
project(NetworkClient)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Укажите путь к Boost
find_package(Boost REQUIRED COMPONENTS system)

# Добавьте исполняемый файл
add_executable(NetworkClient test_client.cpp)

# Свяжите библиотеки Boost
target_include_directories(NetworkClient PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(NetworkClient PRIVATE ${Boost_LIBRARIES})
