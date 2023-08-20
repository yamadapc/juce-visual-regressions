//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookRegistry.h"

namespace juce_visual_regressions {

StorybookRegistry StorybookRegistry::s_instance;

StorybookRegistry::StorybookRegistry()
    : m_rootGroup(std::make_shared<StorybookGroup>("/")) {
}

std::shared_ptr<StorybookGroup>& StorybookRegistry::getRootGroup() {
  return m_rootGroup;
}

StorybookRegistry& StorybookRegistry::getInstance() {
  return s_instance;
}

void StorybookRegistry::shutdown() {
  m_rootGroup = nullptr;
}

} // namespace juce_visual_regressions