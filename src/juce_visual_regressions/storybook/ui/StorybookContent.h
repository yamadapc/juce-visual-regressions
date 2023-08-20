//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include "../model/StorybookRegistry.h"
#include "StorybookSidebar.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace juce_visual_regressions {

using namespace juce;

class StorybookContent : public Component {
public:
  StorybookContent(StorybookRegistry& storybookRegistry)
      : m_storybookSidebar(storybookRegistry) {
    addAndMakeVisible(m_storybookSidebar);
  }

  void resized() override {
    auto bounds = getLocalBounds();
    m_storybookSidebar.setBounds(bounds.removeFromLeft(200));
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StorybookContent)

  StorybookSidebar m_storybookSidebar;
};

} // namespace juce_visual_regressions
