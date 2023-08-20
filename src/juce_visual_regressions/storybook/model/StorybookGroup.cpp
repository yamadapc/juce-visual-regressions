//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookGroup.h"

#include <utility>

namespace juce_visual_regressions {

StorybookGroup::StorybookGroup(std::string mName)
    : m_name(std::move(mName)) {
}

void StorybookGroup::addGroup(std::shared_ptr<StorybookGroup> group) {
  m_children.emplace_back(group);
}

void StorybookGroup::addStory(std::shared_ptr<StorybookStory> story) {
  m_children.emplace_back(story);
}

const std::string& StorybookGroup::getName() {
  return m_name;
}

const std::vector<StorybookGroup::Child>& StorybookGroup::getChildren() {
  return m_children;
}

} // namespace juce_visual_regressions