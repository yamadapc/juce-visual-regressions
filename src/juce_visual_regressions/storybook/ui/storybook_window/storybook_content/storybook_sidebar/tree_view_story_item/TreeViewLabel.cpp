//
// Created by Pedro Tacla Yamada on 26/9/2023.
//

#include "TreeViewLabel.h"

namespace juce_visual_regressions {

TreeViewLabel::TreeViewLabel(StorybookGroup::Child value, ValueTree& state)
    : m_value(std::move(value)),
      m_state(state) {
  m_state.addListener(this);
}

TreeViewLabel::~TreeViewLabel() {
  m_state.removeListener(this);
}

bool TreeViewLabel::isSelected() {
  if(!std::holds_alternative<StorybookStoryRef>(m_value)) {
    return false;
  }

  auto story = std::get<StorybookStoryRef>(m_value);
  auto selectedStoryId = static_cast<int>(m_state.getProperty("selectedStory"));
  if(story->getId() != selectedStoryId) {
    return false;
  }

  return true;
}

void TreeViewLabel::paint(Graphics& g) {
  auto bounds = getLocalBounds();
  g.setColour(isSelected() ? Colours::white : Colour(23, 55, 83));
  g.fillRect(bounds);
  g.setColour(Colours::grey);
  g.drawLine(bounds.getX(),
             bounds.getBottom() - 1,
             bounds.getRight(),
             bounds.getBottom() - 1);
  bounds.removeFromBottom(1);
  bounds.removeFromLeft(10);
  bounds.removeFromRight(10);
  g.setColour(isSelected() ? Colours::black : Colours::white);
  g.drawText(getText(), bounds, Justification::centredLeft);
}

void TreeViewLabel::valueTreePropertyChanged(ValueTree&,
                                             const Identifier& property) {
  if(property != Identifier("selectedStory"))
    return;

  repaint();
}

} // namespace juce_visual_regressions