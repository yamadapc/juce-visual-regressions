//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookContent.h"

namespace juce_visual_regressions {

StorybookContent::StorybookContent(StorybookRegistry& storybookRegistry,
                                   ValueTree& state)
    : m_storybookSidebar(storybookRegistry, state),
      m_state(state) {
  addAndMakeVisible(m_storybookSidebar);
  m_state.addListener(this);
}

void StorybookContent::resized() {
  auto bounds = getLocalBounds();
  m_storybookSidebar.setBounds(bounds.removeFromLeft(200));
  if(m_storyComponent != nullptr) {
    m_storyComponent->setBounds(bounds);
  }
}

void StorybookContent::valueTreePropertyChanged(
  ValueTree& treeWhosePropertyHasChanged,
  const Identifier& property) {
  if(property != Identifier("selectedStory")) {
    return;
  }
  juce::Logger::writeToLog("Selected story changed: " + property.toString());

  if(m_storyComponent != nullptr) {
    juce::Logger::writeToLog("Removing current story");
    removeChildComponent(m_storyComponent.get());
    resized();
  }

  juce::Logger::writeToLog("Updating to new story");
  auto selectedStoryId =
    static_cast<int>(treeWhosePropertyHasChanged.getProperty(property));
  auto maybeStory =
    StorybookRegistry::getInstance().getStoryById(selectedStoryId);

  if(maybeStory.has_value()) {
    m_storyComponent = maybeStory.value()->getComponent();
    addAndMakeVisible(m_storyComponent.get());
    resized();
  }
}

} // namespace juce_visual_regressions