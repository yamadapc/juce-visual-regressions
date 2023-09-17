//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookRegistry.h"

namespace juce_visual_regressions {

StorybookRegistry::StorybookRegistry()
    : m_rootGroup(std::make_shared<StorybookGroup>("/")) {
}

std::optional<std::shared_ptr<StorybookStory>>
StorybookRegistry::getStoryById(int id) {
  return m_rootGroup->getStoryById(id);
}

std::shared_ptr<StorybookGroup>& StorybookRegistry::getRootGroup() {
  return m_rootGroup;
}

StorybookRegistry& StorybookRegistry::getInstance() {
  static StorybookRegistry s_instance;
  assert(s_instance.m_rootGroup != nullptr);
  return s_instance;
}

void StorybookRegistry::shutdown() {
  m_rootGroup = nullptr;
}

} // namespace juce_visual_regressions