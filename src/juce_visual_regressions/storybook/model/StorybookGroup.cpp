//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookGroup.h"

#include <utility>

namespace juce_visual_regressions {

StorybookGroup::StorybookGroup(std::string mName)
    : m_name(std::move(mName)) {
}

std::optional<StorybookStoryRef> StorybookGroup::getStoryById(int id) {
  for(auto& child : m_children) {
    if(const auto& story = std::get_if<StorybookStoryRef>(&child)) {
      if((*story)->getId() == id) {
        return *story;
      }
    } else if(const auto& group = std::get_if<StorybookGroupRef>(&child)) {
      if(auto childStory = (*group)->getStoryById(id)) {
        return childStory;
      }
    }
  }
  return std::nullopt;
}

void StorybookGroup::addGroup(StorybookGroupRef group) {
  m_children.emplace_back(group);
}

void StorybookGroup::addStory(StorybookStoryRef story) {
  m_children.emplace_back(story);
}

const std::string& StorybookGroup::getName() {
  return m_name;
}

const std::vector<StorybookGroup::Child>& StorybookGroup::getChildren() {
  return m_children;
}

} // namespace juce_visual_regressions