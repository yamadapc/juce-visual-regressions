//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include "../../../../../model/StorybookGroup.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace juce_visual_regressions {

using namespace juce;

class TreeViewStoryItem : public TreeViewItem {
public:
  TreeViewStoryItem(StorybookGroup::Child value, ValueTree& state);

  bool mightContainSubItems() override;
  [[nodiscard]] bool canBeSelected() const override;
  [[nodiscard]] String getUniqueName() const override;
  std::unique_ptr<Component> createItemComponent() override;
  [[nodiscard]] bool customComponentUsesTreeViewMouseHandler() const override;

    int getItemHeight() const override;

    void itemSelectionChanged(bool isNowSelected) override;
  void itemOpennessChanged(bool isNowOpen) override;

private:
  void setupChildren();

  StorybookGroup::Child m_value;
  ValueTree& m_state;
};

} // namespace juce_visual_regressions
