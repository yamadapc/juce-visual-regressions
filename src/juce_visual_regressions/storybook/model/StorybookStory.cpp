//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookStory.h"

namespace juce_visual_regressions {

static int getNextId() {
  static int id = 0;
  return id++;
}

StorybookStory::StorybookStory(std::string name,
                               std::function<juce::Component*()> block)
    : m_id(getNextId()),
      m_name(name),
      m_block(block) {
}

const int StorybookStory::getId() const {
  return m_id;
}

const std::string& StorybookStory::getName() const {
  return m_name;
}

const std::function<juce::Component*()>& StorybookStory::getBlock() const {
  return m_block;
}

} // namespace juce_visual_regressions