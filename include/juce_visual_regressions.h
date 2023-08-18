#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define JUCE_VISUAL_REGRESSIONS_EXPORT __declspec(dllexport)
#else
  #define JUCE_VISUAL_REGRESSIONS_EXPORT
#endif

JUCE_VISUAL_REGRESSIONS_EXPORT void juce_visual_regressions();
JUCE_VISUAL_REGRESSIONS_EXPORT void juce_visual_regressions_print_vector(const std::vector<std::string> &strings);
