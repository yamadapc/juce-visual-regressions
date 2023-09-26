//
// Created by Pedro Tacla Yamada on 23/9/2023.
//

#include "StorybookStoryFrame.h"

namespace juce_visual_regressions {

StorybookStoryFrame::StorybookStoryFrame(ValueTree& state)
    : m_state(state) {
  m_state.addListener(this);
  onStoryChanged();
}

StorybookStoryFrame::~StorybookStoryFrame() {
  m_state.removeListener(this);
}

void StorybookStoryFrame::paint(Graphics& g) {
  auto bounds = getLocalBounds();

  g.setColour(Colours::black);
  auto path = Path();
  path.addRoundedRectangle(bounds.reduced(20).toFloat(), 10);
  g.fillPath(path);
  auto dropShadow =
    DropShadow(Colours::black.withAlpha(0.5f), 5, Point<int>(0, 0));
  dropShadow.drawForPath(g, path);
}

void StorybookStoryFrame::resized() {
  if(m_storyComponent == nullptr) {
    return;
  }
  m_storyComponent->setBounds(getLocalBounds().reduced(30));
}

void StorybookStoryFrame::valueTreePropertyChanged(ValueTree&,
                                                   const Identifier& property) {
  if(property != Identifier("selectedStory")) {
    return;
  }

  onStoryChanged();
}

void StorybookStoryFrame::onStoryChanged() {
  juce::Logger::writeToLog("Selected story changed");
  if(m_storyComponent != nullptr) {
    juce::Logger::writeToLog("Removing current story");
    removeChildComponent(m_storyComponent.get());
    resized();
  }

  auto selectedStoryId = static_cast<int>(m_state.getProperty("selectedStory"));
  juce::Logger::writeToLog("Updating to new story id=" +
                           String(selectedStoryId));
  auto maybeStory =
    StorybookRegistry::getInstance().getStoryById(selectedStoryId);

  if(!maybeStory.has_value()) {
    return;
  }

  m_story = maybeStory.value();
  m_storyComponent = std::shared_ptr<Component>((m_story->getBlock())());
  addAndMakeVisible(m_storyComponent.get());
  resized();
}

} // namespace juce_visual_regressions