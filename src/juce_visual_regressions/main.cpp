#include <juce_gui_basics/juce_gui_basics.h>

#include "SnapshotTester.h"

int main () {
  using namespace juce_visual_regressions;
  using namespace juce;

  SnapshotTester tester;

  testComponent ([] () {
    TextButton component = TextButton ("Hello World");
    component.setBounds ({0, 0, 100, 100});
    matchesSnapshot (component, "test");
  });

  return 0;
}