//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookContent.h"

namespace juce_visual_regressions {

StorybookContent::StorybookContent(StorybookRegistry& storybookRegistry,
                                   ValueTree& state)
    : m_storybookSidebar(storybookRegistry, state),
      m_storybookStoryFrame(state),
      m_state(state) {
  addAndMakeVisible(m_storybookSidebar);
  addAndMakeVisible(m_storybookStoryFrame);
}

void StorybookContent::paint(juce::Graphics& g) {
  auto bounds = getLocalBounds();
  g.setColour(Colour(23, 55, 83));
  g.fillRect(bounds);
}

void StorybookContent::resized() {
  auto bounds = getLocalBounds();
  m_storybookSidebar.setBounds(bounds.removeFromLeft(200));
  m_storybookStoryFrame.setBounds(bounds);
}

} // namespace juce_visual_regressions