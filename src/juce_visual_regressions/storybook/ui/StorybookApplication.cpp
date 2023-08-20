//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookApplication.h"

namespace juce_visual_regressions {

StorybookApplication::StorybookApplication()
    : m_storybookRegistry(StorybookRegistry::getInstance()),
      m_state("StorybookState")
{
  auto& rootGroup = m_storybookRegistry.getRootGroup();
  auto group = std::make_shared<StorybookGroup>("Test group");
  rootGroup->addGroup(group);
  auto story = std::make_shared<StorybookStory>(
    "Test story", std::make_shared<TextButton>("Test button"));
  rootGroup->addStory(story);

  m_mainWindow =
    std::make_unique<StorybookWindow>(m_storybookRegistry, m_state);
}

const String StorybookApplication::getApplicationName() {
  return "Storybook";
}

const String StorybookApplication::getApplicationVersion() {
  return "0.1.0";
}

void StorybookApplication::initialise(const String& commandLineParameters) {
  m_mainWindow->setVisible(true);
}

void StorybookApplication::shutdown() {
  m_mainWindow = nullptr;
  m_storybookRegistry.shutdown();
}

} // namespace juce_visual_regressions