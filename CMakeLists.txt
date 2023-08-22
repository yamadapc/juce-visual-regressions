cmake_minimum_required(VERSION 3.14)

project(juce_visual_regressions VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

set(
        PRIVATE_DEPENDENCIES
        juce::juce_gui_basics
)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_LIST_DIR}/src/juce_visual_regressions/*.cpp"
)

# check if JUCE is loaded
if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
find_package(JUCE GLOBAL)

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
juce_generate_juce_header(StoryBook)
target_sources(
        StoryBook
        PRIVATE
        ${PROJECT_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
target_link_libraries(
        StoryBook
        PRIVATE
        ${PRIVATE_DEPENDENCIES}
)

endif()

add_library(juce_visual_regressions)
set(juce_visual_regressions_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/generated")

target_sources(
        juce_visual_regressions
        PRIVATE
        ${PROJECT_SOURCES}
)

target_link_libraries(
        juce_visual_regressions
        PRIVATE
        ${PRIVATE_DEPENDENCIES}
)

install(
        TARGETS
        juce_visual_regressions
        EXPORT juce_visual_regressions
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)