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

  std::optional<StorybookStoryRef> getStoryById(int id);
  StorybookGroupRef& getRootGroup();
  void shutdown();

  static StorybookRegistry& getInstance();

private:
  StorybookGroupRef m_rootGroup;
};

} // namespace juce_visual_regressions
