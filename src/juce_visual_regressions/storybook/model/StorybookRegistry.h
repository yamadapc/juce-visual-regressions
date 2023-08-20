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

  std::shared_ptr<StorybookGroup>& getRootGroup();

  static StorybookRegistry& getInstance();

  void shutdown();

private:
  std::shared_ptr<StorybookGroup> m_rootGroup;
  static StorybookRegistry s_instance;
};

} // namespace juce_visual_regressions
