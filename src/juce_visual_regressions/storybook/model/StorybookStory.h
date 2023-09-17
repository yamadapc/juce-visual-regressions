//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace juce_visual_regressions {

class StorybookStory {
public:
  StorybookStory(std::string name, std::function<juce::Component*()> block);

  const int getId() const;
  const std::string& getName() const;
  const std::function<juce::Component*()>& getBlock() const;

private:
  int m_id;
  std::string m_name;
  std::function<juce::Component*()> m_block;
};

} // namespace juce_visual_regressions
