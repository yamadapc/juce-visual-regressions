cmake_minimum_required(VERSION 3.14)

project(juce_visual_regressions VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

set(PRIVATE_DEPENDENCIES juce::juce_gui_basics)

file(
  GLOB_RECURSE
  JUCE_VR_PROJECT_SOURCES
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_LIST_DIR}/src/juce_visual_regressions/*.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/src/juce_visual_regressions/*.h"
)

# check if JUCE is loaded
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  find_package(JUCE GLOBAL)
  
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
  target_link_options(StoryBook PRIVATE -Wl,-weak_reference_mismatches,weak)
  target_compile_definitions(StoryBook PRIVATE JUCE_VR_IS_STORYBOOK=1)
  juce_generate_juce_header(StoryBook)
  target_sources(
    StoryBook
    PUBLIC ${JUCE_VR_PROJECT_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  )
  target_link_libraries(
    StoryBook
    PRIVATE juce::juce_gui_basics
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
    ${PUBLIC_DEPENDENCIES}
  )
  
endif()

add_library(juce_visual_regressions)
set(juce_visual_regressions_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/generated")

target_sources(juce_visual_regressions PUBLIC ${JUCE_VR_PROJECT_SOURCES})
target_include_directories(
  juce_visual_regressions
  PUBLIC ${juce_visual_regressions_INCLUDE_DIR}
)
target_link_libraries(juce_visual_regressions PRIVATE ${PRIVATE_DEPENDENCIES})
install(
  TARGETS juce_visual_regressions
  EXPORT juce_visual_regressions
  LIBRARY
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  INCLUDES
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  message(STATUS "Building as a standalone project")
else()
  set(JUCE_VR_DIR ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
  message(STATUS "Building as a subproject")
endif()


function(juce_vr_add_storybook NAME)
  juce_add_gui_app(${NAME})
  message(STATUS "Adding storybook ${NAME}")
  message(STATUS "-- VR Dir - ${JUCE_VR_DIR}")
  target_sources(${NAME} PRIVATE ${JUCE_VR_DIR}/src/main.cpp)
  target_link_libraries(
    ${NAME}
    PRIVATE juce::juce_gui_basics
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
    juce_visual_regressions
  )
  target_compile_definitions(
    ${NAME}
    PRIVATE
    JUCE_VR_STORYBOOK_NAME=${JUCE_VR_ADD_STORYBOOK_NAME}
    JUCE_VR_IS_STORYBOOK=1
  )
endfunction()