cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(juce_visual_regressions)

add_executable(example src/example.cpp)
target_link_libraries(example juce_visual_regressions::juce_visual_regressions)
