//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include <utility>

#include "TreeViewLabel.h"
#include "TreeViewStoryItem.h"

namespace juce_visual_regressions {

TreeViewStoryItem::TreeViewStoryItem(StorybookGroup::Child value,
                                     ValueTree& state)
    : m_value(std::move(value)),
      m_state(state) {
  setupChildren();
  m_state.addListener(this);
}

bool TreeViewStoryItem::mightContainSubItems() {
  if(std::holds_alternative<StorybookGroupRef>(m_value)) {
    return true;
  } else {
    return false;
  }
}

String TreeViewStoryItem::getUniqueName() const {
  if(std::holds_alternative<StorybookGroupRef>(m_value)) {
    return std::get<StorybookGroupRef>(m_value)->getName();
  } else {
    return std::get<StorybookStoryRef>(m_value)->getName();
  }
}

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
  if(!std::holds_alternative<StorybookStoryRef>(m_value))
    return;

  auto story = std::get<StorybookStoryRef>(m_value);
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
  if(!std::holds_alternative<StorybookGroupRef>(m_value))
    return;

  auto group = std::get<StorybookGroupRef>(m_value);
  for(auto& child : group->getChildren()) {
    addSubItem(new TreeViewStoryItem(child, m_state));
  }
}

int TreeViewStoryItem::getItemHeight() const {
  return 40;
}

} // namespace juce_visual_regressions