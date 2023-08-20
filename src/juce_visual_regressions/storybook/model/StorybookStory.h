//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace juce_visual_regressions {

class StorybookStory {
public:
  StorybookStory(std::string name, std::shared_ptr<juce::Component> component);

  const std::string& getName() const;
  const std::shared_ptr<juce::Component>& getComponent() const;

private:
  std::string m_name;
  std::shared_ptr<juce::Component> m_component;
};

} // namespace juce_visual_regressions
