cmake_minimum_required(VERSION 3.14)

project(juce_visual_regressions VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(JUCE)
add_subdirectory(vendor/fmt)

juce_add_gui_app(
        StoryBook
        PRODUCT_NAME "BF StoryBook"
        COMPANY_NAME "Pedro Tacla Yamada"
)

set_target_properties(
        StoryBook
        PROPERTIES
        JUCE_GENERATED_SOURCES_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/generated"
)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/generated")
juce_generate_juce_header(StoryBook)

target_sources(
        StoryBook
        PRIVATE
        src/main.cpp
)
set(
        PRIVATE_DEPENDENCIES
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
        juce::juce_gui_basics
        fmt
)
target_link_libraries(
        StoryBook
        PRIVATE
        ${PRIVATE_DEPENDENCIES}
        PUBLIC
        ${PUBLIC_DEPENDENCIES}
)