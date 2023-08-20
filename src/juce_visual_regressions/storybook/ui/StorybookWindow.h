//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include "../model/StorybookRegistry.h"
#include "StorybookContent.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace juce_visual_regressions {

using namespace juce;

class StorybookWindow : public DocumentWindow {
public:
  StorybookWindow(StorybookRegistry& storybookRegistry, ValueTree& state);

  void closeButtonPressed() override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StorybookWindow)

  StorybookRegistry& m_storybookRegistry;
  StorybookContent m_storybookContent;
};

} // namespace juce_visual_regressions
