//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookSidebar.h"

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

std::unique_ptr<Component> TreeViewStoryItem::createItemComponent() {
  auto label = std::make_unique<Label>();
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

StorybookSidebar::StorybookSidebar(StorybookRegistry& storybookRegistry,
                                   ValueTree& state)
    : m_storybookRegistry(storybookRegistry),
      m_state(state),
      m_rootItem(m_storybookRegistry.getRootGroup(), state) {
  addAndMakeVisible(&m_treeView);

  m_treeView.setDefaultOpenness(true);
  m_treeView.setRootItem(&m_rootItem);
}

void StorybookSidebar::paint(Graphics& g) {
  Path path;
  auto width = static_cast<float>(getWidth());
  auto height = static_cast<float>(getHeight());
  path.addLineSegment(Line<float>(width - 1.0f, 0.0f, width - 1.0f, height),
                      1.0f);
  g.setColour(Colours::grey);
  g.strokePath(path, PathStrokeType(1.0f));
}

void StorybookSidebar::resized() {
  auto bounds = getLocalBounds();
  m_treeView.setBounds(bounds);
}

} // namespace juce_visual_regressions