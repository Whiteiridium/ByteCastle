cmake_minimum_required(VERSION 3.10)
project(ByteCastle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создание папки build
#if(NOT EXISTS "${CMAKE_BINARY_DIR}/build")
#    message(STATUS "Creating build directory in ${CMAKE_BINARY_DIR}/build")
#    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/build")
#else()
#    message(STATUS "Build directory already exists")
#endif()

# Условие для Linux
if(UNIX AND NOT APPLE)
    message(STATUS "Configuring for Ubuntu (Linux)...")
    find_package(Boost REQUIRED COMPONENTS system)

    add_library(server_lib STATIC 
        Headers/NetworkModule.h
        Source/NetworkModule.cpp
    )

    add_executable(FTP main.cpp)
    target_link_libraries(FTP server_lib Boost::system)

# Условие для Windows
elseif(WIN32)
    message(STATUS "Configuring for Windows...")

    # Указываем путь до Boost для Windows
    set(BOOST_ROOT "C:/path/to/boost")
    set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
    set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")

    find_package(Boost REQUIRED COMPONENTS system)

    add_library(server_lib STATIC 
        Headers/NetworkModule.h
        Source/NetworkModule.cpp
    )

    add_executable(FTP main.cpp)

    target_link_libraries(FTP server_lib Boost::system)

else()
    message(FATAL_ERROR "Unsupported OS")
endif()
