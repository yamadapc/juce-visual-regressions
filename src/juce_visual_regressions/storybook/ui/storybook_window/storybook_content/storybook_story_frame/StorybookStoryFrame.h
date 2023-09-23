//
// Created by Pedro Tacla Yamada on 23/9/2023.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../../../model/StorybookRegistry.h"
#include "../../../../model/StorybookStory.h"

namespace juce_visual_regressions {

using namespace juce;

class StorybookStoryFrame : public Component, public ValueTree::Listener {
public:
  explicit StorybookStoryFrame(ValueTree& state)
      : m_state(state) {
    m_state.addListener(this);
  }

  ~StorybookStoryFrame() override {
    m_state.removeListener(this);
  }

  void paint(Graphics& g) override {
    auto bounds = getLocalBounds();

    g.setColour(Colours::black);
    auto path = Path();
    path.addRoundedRectangle(bounds.reduced(20).toFloat(), 10);
    g.fillPath(path);
    DropShadow dropShadow(Colours::black.withAlpha(0.5f), 5, Point<int>(0, 0));
    dropShadow.drawForPath(g, path);
  }

  void resized() override {
    if(m_storyComponent != nullptr) {
      m_storyComponent->setBounds(getLocalBounds().reduced(30));
    }
  }

  void valueTreePropertyChanged(ValueTree&,
                                const Identifier& property) override {
    if(property != Identifier("selectedStory")) {
      return;
    }

    onStoryChanged();
  }

private:
  void onStoryChanged() {
    auto property = Identifier("selectedStory");

    juce::Logger::writeToLog("Selected story changed: " + property.toString());
    if(m_storyComponent != nullptr) {
      juce::Logger::writeToLog("Removing current story");
      removeChildComponent(m_storyComponent.get());
      resized();
    }

    juce::Logger::writeToLog("Updating to new story");
    auto selectedStoryId = static_cast<int>(m_state.getProperty(property));
    auto maybeStory =
      StorybookRegistry::getInstance().getStoryById(selectedStoryId);

    if(maybeStory.has_value()) {
      m_story = maybeStory.value();
      m_storyComponent = std::shared_ptr<Component>((m_story->getBlock())());
      addAndMakeVisible(m_storyComponent.get());
      resized();
    }
  }

  ValueTree& m_state;
  std::shared_ptr<Component> m_storyComponent = nullptr;
  std::shared_ptr<StorybookStory> m_story = nullptr;
};

} // namespace juce_visual_regressions
