//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookApplication.h"
#include "JuceHeader.h"

namespace juce_visual_regressions {

StorybookApplication::StorybookApplication()
    : m_storybookRegistry(StorybookRegistry::getInstance()),
      m_mainWindow(std::make_unique<StorybookWindow>(m_storybookRegistry)) {
}

const String StorybookApplication::getApplicationName() {
  return "Storybook";
}

const String StorybookApplication::getApplicationVersion() {
  return ProjectInfo::versionString;
}

void StorybookApplication::initialise(const String& commandLineParameters) {
  m_mainWindow->setVisible(true);

  auto& rootGroup = m_storybookRegistry.getRootGroup();
  auto group = std::make_shared<StorybookGroup>("Test group");
  rootGroup->addGroup(group);
  auto story = std::make_shared<StorybookStory>(
    "Test story", std::make_shared<TextButton>("Test button"));
  rootGroup->addStory(story);
}

void StorybookApplication::shutdown() {
  m_mainWindow = nullptr;
  m_storybookRegistry.shutdown();
}

} // namespace juce_visual_regressions