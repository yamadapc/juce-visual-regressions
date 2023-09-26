//
// Created by Pedro Tacla Yamada on 23/9/2023.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../../../model/StorybookRegistry.h"
#include "juce_visual_regressions/storybook/model/storybook_story/StorybookStory.h"

namespace juce_visual_regressions {

using namespace juce;

class StorybookStoryFrame : public Component, public ValueTree::Listener {
public:
  explicit StorybookStoryFrame(ValueTree& state);

  ~StorybookStoryFrame() override;

  void paint(Graphics& g) override;
  void resized() override;

  void valueTreePropertyChanged(ValueTree&,
                                const Identifier& property) override;

private:
  void onStoryChanged();

  ValueTree& m_state;
  std::shared_ptr<Component> m_storyComponent = nullptr;
  StorybookStoryRef m_story = nullptr;
};

} // namespace juce_visual_regressions
