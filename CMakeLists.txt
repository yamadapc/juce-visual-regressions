cmake_minimum_required(VERSION 3.14)

project(juce_visual_regressions VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

# conan_basic_setup()

find_package(fmt)
find_package(JUCE)

add_definitions(-DJUCE_DISPLAY_SPLASH_SCREEN=0)

juce_add_gui_app(
        StoryBook
        PRODUCT_NAME "BF StoryBook"
        COMPANY_NAME "Pedro Tacla Yamada"
        BUNDLE_ID "com.beijaflor.juce_storybook"
)

set_target_properties(
        StoryBook
        PROPERTIES
        JUCE_GENERATED_SOURCES_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/generated"
)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/generated")
juce_generate_juce_header(StoryBook)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
)

target_sources(
        StoryBook
        PRIVATE
        ${PROJECT_SOURCES}
)

set(
        PRIVATE_DEPENDENCIES
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
        juce::juce_gui_basics
        fmt::fmt
)

target_link_libraries(
        StoryBook
        PRIVATE
        ${PRIVATE_DEPENDENCIES}
        PUBLIC
        ${PUBLIC_DEPENDENCIES}
)

# add_subdirectory(./examples/todo_list)