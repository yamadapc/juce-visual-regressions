//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include "../../../../model/StorybookRegistry.h"
#include "tree_view_story_item/TreeViewStoryItem.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace juce_visual_regressions {

using namespace juce;

class StorybookSidebar : public Component {
public:
  StorybookSidebar(StorybookRegistry& storybookRegistry, ValueTree& state);

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
