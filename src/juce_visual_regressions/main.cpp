// #include <juce_gui_basics/juce_gui_basics.h>
//
// #include "SnapshotTester.h"
//
// int main() {
//   using namespace juce_visual_regressions;
//   using namespace juce;
//
//   SnapshotTester tester;
//
//   Logger::writeToLog("Starting tests...");
//
//   testComponent([]() {
//     TextButton component = TextButton("Hello World");
//     component.setBounds({0, 0, 100, 100});
//     matchesSnapshot(component, "test");
//   });
//
//   Logger::writeToLog("Tests complete.");
//
//   return 0;
// }

#include "JuceHeader.h"
#include "storybook/ui/StorybookApplication.h"

START_JUCE_APPLICATION(juce_visual_regressions::StorybookApplication)