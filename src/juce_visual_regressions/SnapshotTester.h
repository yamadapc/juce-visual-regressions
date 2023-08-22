#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace juce_visual_regressions {

using namespace juce;

Optional<File> getRootProjectDirectory(const File& file);
void matchesSnapshot(Component& component, std::string_view name);
void testComponent(const std::function<void()>& test);
void runComponentSnapshotTest(std::string_view name, std::function<Component* ()> test);

struct Snapshot {
  juce::Image image;
};

class SnapshotTester {
public:
  SnapshotTester() = default;

  Snapshot takeSnapshot(juce::Component& component);
};

} // namespace juce_visual_regressions