//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include "../../../model/StorybookRegistry.h"
#include "./storybook_sidebar/StorybookSidebar.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace juce_visual_regressions {

using namespace juce;

class StorybookContent : public Component, public ValueTree::Listener {
public:
  StorybookContent(StorybookRegistry& storybookRegistry, ValueTree& state);

  void valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged,
                                const Identifier& property) override;

  void paint(Graphics& g) override;
  void resized() override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StorybookContent)

  StorybookSidebar m_storybookSidebar;
  ValueTree m_state;
  std::shared_ptr<Component> m_storyComponent;
};

} // namespace juce_visual_regressions
