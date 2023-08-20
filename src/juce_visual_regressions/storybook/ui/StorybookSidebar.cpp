//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookSidebar.h"

namespace juce_visual_regressions {

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

void TreeViewStoryItem::itemOpennessChanged(bool isNowOpen) {
  if(!isNowOpen)
    return;
  if(!std::holds_alternative<std::shared_ptr<StorybookGroup>>(m_value))
    return;

  auto group = std::get<std::shared_ptr<StorybookGroup>>(m_value);
  for(auto& child : group->getChildren()) {
    addSubItem(new TreeViewStoryItem(child));
  }
}

StorybookSidebar::StorybookSidebar(StorybookRegistry& storybookRegistry)
  : m_storybookRegistry(storybookRegistry),
    m_rootItem(m_storybookRegistry.getRootGroup()) {
  addAndMakeVisible(&m_treeView);

  m_treeView.setRootItem(&m_rootItem);
}
} // namespace juce_visual_regressions