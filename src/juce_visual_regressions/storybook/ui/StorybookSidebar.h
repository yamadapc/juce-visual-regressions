//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include "../model/StorybookRegistry.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace juce_visual_regressions {

using namespace juce;

class TreeViewStoryItem : public TreeViewItem {
public:
  TreeViewStoryItem(StorybookGroup::Child value, ValueTree& state);

  bool mightContainSubItems() override;
  bool canBeSelected() const override;
  [[nodiscard]] String getUniqueName() const override;
  std::unique_ptr<Component> createItemComponent() override;
  bool customComponentUsesTreeViewMouseHandler() const override;
  void itemSelectionChanged(bool isNowSelected) override;
  void itemOpennessChanged(bool isNowOpen) override;

private:
  void setupChildren();

  StorybookGroup::Child m_value;
  ValueTree& m_state;
};

class StorybookSidebar : public Component {
public:
  explicit StorybookSidebar(StorybookRegistry& storybookRegistry, ValueTree& state);

  void paint(Graphics& g) override;
  void resized() override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StorybookSidebar)

  StorybookRegistry& m_storybookRegistry;
  ValueTree& m_state;
  TreeView m_treeView;
  TreeViewStoryItem m_rootItem;
};

} // namespace juce_visual_regressions
