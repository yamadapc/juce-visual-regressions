#include "juce_visual_regressions.h"
#include <vector>
#include <string>

int main() {
    juce_visual_regressions();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    juce_visual_regressions_print_vector(vec);
}
