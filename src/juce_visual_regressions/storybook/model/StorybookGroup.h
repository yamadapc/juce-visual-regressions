//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include <string>
#include <variant>
#include <vector>

#include "juce_visual_regressions/storybook/model/storybook_story/StorybookStory.h"

namespace juce_visual_regressions {

class StorybookGroup;
using StorybookStoryRef = std::shared_ptr<StorybookStory>;
using StorybookGroupRef = std::shared_ptr<StorybookGroup>;

class StorybookGroup {
public:
  using Child = std::variant<StorybookGroupRef, StorybookStoryRef>;

  explicit StorybookGroup(std::string mName);

  std::optional<StorybookStoryRef> getStoryById(int id);
  void addGroup(StorybookGroupRef group);
  void addStory(StorybookStoryRef story);

  const std::string& getName();
  const std::vector<Child>& getChildren();

private:
  std::string m_name;
  std::vector<Child> m_children;
};

} // namespace juce_visual_regressions
