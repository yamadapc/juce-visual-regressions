//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "TreeViewStoryItem.h"

#include <utility>

namespace juce_visual_regressions {

TreeViewStoryItem::TreeViewStoryItem(StorybookGroup::Child value,
                                     ValueTree& state)
    : m_value(std::move(value)),
      m_state(state) {
  setupChildren();
}

bool TreeViewStoryItem::mightContainSubItems() {
  if(std::holds_alternative<std::shared_ptr<StorybookGroup>>(m_value)) {
    return true;
  } else {
    return false;
  }
}

String TreeViewStoryItem::getUniqueName() const {
  if(std::holds_alternative<std::shared_ptr<StorybookGroup>>(m_value)) {
    return std::get<std::shared_ptr<StorybookGroup>>(m_value)->getName();
  } else {
    return std::get<std::shared_ptr<StorybookStory>>(m_value)->getName();
  }
}

class TreeViewLabel : public Label {
public:
  TreeViewLabel(StorybookGroup::Child value, ValueTree& state)
      : m_value(std::move(value)),
        m_state(state) {
    setRepaintsOnMouseActivity(true);
  }

  bool isSelected() {
    if(!std::holds_alternative<std::shared_ptr<StorybookStory>>(m_value)) {
      return false;
    }

    auto story = std::get<std::shared_ptr<StorybookStory>>(m_value);
    auto selectedStoryId =
      static_cast<int>(m_state.getProperty("selectedStory", -1));
    if(story->getId() != selectedStoryId) {
      return false;
    }

    return true;
  }

  void paint(Graphics& g) override {
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

private:
  StorybookGroup::Child m_value;
  ValueTree& m_state;
};

std::unique_ptr<Component> TreeViewStoryItem::createItemComponent() {
  auto label = std::make_unique<TreeViewLabel>(m_value, m_state);
  label->setText(getUniqueName(), dontSendNotification);
  label->setColour(Label::textColourId, Colours::black);
  return label;
}

bool TreeViewStoryItem::canBeSelected() const {
  return true;
}

void TreeViewStoryItem::itemSelectionChanged(bool isNowSelected) {
  if(!isNowSelected)
    return;
  if(!std::holds_alternative<std::shared_ptr<StorybookStory>>(m_value))
    return;

  auto story = std::get<std::shared_ptr<StorybookStory>>(m_value);
  m_state.setProperty("selectedStory", story->getId(), nullptr);
  repaintItem();
}

bool TreeViewStoryItem::customComponentUsesTreeViewMouseHandler() const {
  return true;
}

void TreeViewStoryItem::itemOpennessChanged(bool isNowOpen) {
  if(!isNowOpen)
    return;
  setupChildren();
}

void TreeViewStoryItem::setupChildren() {
  if(getNumSubItems() > 0)
    return;
  if(!std::holds_alternative<std::shared_ptr<StorybookGroup>>(m_value))
    return;

  auto group = std::get<std::shared_ptr<StorybookGroup>>(m_value);
  for(auto& child : group->getChildren()) {
    addSubItem(new TreeViewStoryItem(child, m_state));
  }
}

int TreeViewStoryItem::getItemHeight() const {
  return 40;
}

} // namespace juce_visual_regressions