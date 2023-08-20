//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include <string>
#include <variant>
#include <vector>

#include "StorybookStory.h"

namespace juce_visual_regressions {

class StorybookGroup {
public:
  using Child = std::variant<std::shared_ptr<StorybookGroup>,
                             std::shared_ptr<StorybookStory>>;

  explicit StorybookGroup(std::string  mName);

  void addGroup(std::shared_ptr<StorybookGroup> group);
  void addStory(std::shared_ptr<StorybookStory> story);

  const std::string& getName();
  const std::vector<Child>& getChildren();

private:
  std::string m_name;
  std::vector<Child> m_children;
};

} // namespace juce_visual_regressions
