//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include <vector>

#include "StorybookGroup.h"
#include "StorybookStory.h"

namespace juce_visual_regressions {

class StorybookRegistry {
public:
  StorybookRegistry();

  std::optional<std::shared_ptr<StorybookStory>> getStoryById(int id);
  std::shared_ptr<StorybookGroup>& getRootGroup();
  void shutdown();

  static StorybookRegistry& getInstance();

private:
  std::shared_ptr<StorybookGroup> m_rootGroup;
};

} // namespace juce_visual_regressions
