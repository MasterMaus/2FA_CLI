cmake_minimum_required(VERSION 3.23)
project(2FA_CLI VERSION 0.1)


set(CMAKE_CXX_STANDARD 20)

FIND_PACKAGE(Boost REQUIRED)
## FIND_PACKAGE(Boost 1.45 COMPONENTS filesystem regex REQUIRED)
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

add_executable(2fa main.cpp Options.h InputParser.h TokenGenerator.h TokenGenerator.cpp Key.h NotImplementedException.h InvalidArgumentsException.h Options.cpp)

