//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookRegistry.h"
#include <cassert>

namespace juce_visual_regressions {

StorybookRegistry::StorybookRegistry()
    : m_rootGroup(std::make_shared<StorybookGroup>("/")) {
}

std::optional<StorybookStoryRef>
StorybookRegistry::getStoryById(int id) {
  return m_rootGroup->getStoryById(id);
}

StorybookGroupRef& StorybookRegistry::getRootGroup() {
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