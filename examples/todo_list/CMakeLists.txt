cmake_minimum_required(VERSION 3.14)

project(juce_visual_regressions VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

# if included into another project
if(NOT TARGET juce::juce_gui_basics)
add_subdirectory(../../JUCE ${CMAKE_CURRENT_BINARY_DIR}/JUCE)
add_subdirectory(../../vendor/fmt ${CMAKE_CURRENT_BINARY_DIR}/fmt)
endif()

juce_add_gui_app(
        TodoList
        PRODUCT_NAME "BF StoryBook - Todo list example"
        COMPANY_NAME "Pedro Tacla Yamada"
        BUNDLE_ID "com.beijaflor.juce_storybook.todolist"
)

set_target_properties(
        TodoList
        PROPERTIES
        JUCE_GENERATED_SOURCES_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/generated"
)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/generated")
juce_generate_juce_header(TodoList)

target_sources(
        TodoList
        PRIVATE
        main.cpp
)
set(
        PRIVATE_DEPENDENCIES
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
        juce::juce_gui_basics
        juce::
        fmt
)
target_link_libraries(
        TodoList
        PRIVATE
        ${PRIVATE_DEPENDENCIES}
        PUBLIC
        ${PUBLIC_DEPENDENCIES}
)