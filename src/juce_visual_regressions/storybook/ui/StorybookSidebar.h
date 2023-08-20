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
  TreeViewStoryItem(StorybookGroup::Child value)
      : m_value(std::move(value)) {
  }

  bool mightContainSubItems() override;
  String getUniqueName() const override;
  void itemOpennessChanged(bool isNowOpen) override;
  std::unique_ptr<Component> createItemComponent() override;

private:
  StorybookGroup::Child m_value;
};

class StorybookSidebar : public Component {
public:
  explicit StorybookSidebar(StorybookRegistry& storybookRegistry);

  void paint(Graphics& g) override {
    Path path;
    path.addLineSegment(
      Line<float>(getWidth() - 1, 0, getWidth() - 1, getHeight()), 1.0f);
    g.setColour(Colours::grey);
    g.strokePath(path, PathStrokeType(1.0f));
  }

  void resized() override {
    auto bounds = getLocalBounds();
    m_treeView.setBounds(bounds);
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StorybookSidebar)

  StorybookRegistry& m_storybookRegistry;
  TreeView m_treeView;
  TreeViewStoryItem m_rootItem;
};

} // namespace juce_visual_regressions
