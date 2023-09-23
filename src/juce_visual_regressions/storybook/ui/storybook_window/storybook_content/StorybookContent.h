//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../../model/StorybookRegistry.h"
#include "./storybook_sidebar/StorybookSidebar.h"
#include "./storybook_story_frame/StorybookStoryFrame.h"

namespace juce_visual_regressions {

using namespace juce;

class StorybookContent : public Component {
public:
  StorybookContent(StorybookRegistry& storybookRegistry, ValueTree& state);

  void paint(Graphics& g) override;
  void resized() override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StorybookContent)

  StorybookSidebar m_storybookSidebar;
  StorybookStoryFrame m_storybookStoryFrame;
  ValueTree m_state;
  std::shared_ptr<Component> m_storyComponent;
};

} // namespace juce_visual_regressions
