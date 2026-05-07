cmake_minimum_required(VERSION 3.10)
project(BoostExample)

find_package(Boost REQUIRED)

add_executable(beastie src/main.cpp src/utils.cpp)
target_include_directories(beastie PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(beastie PRIVATE include)
