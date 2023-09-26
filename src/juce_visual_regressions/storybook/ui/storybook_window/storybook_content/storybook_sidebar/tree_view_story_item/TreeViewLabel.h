//
// Created by Pedro Tacla Yamada on 26/9/2023.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../../../../model/StorybookGroup.h"

namespace juce_visual_regressions {

using namespace juce;

class TreeViewLabel : public Label, public ValueTree::Listener {
public:
  TreeViewLabel(StorybookGroup::Child value, ValueTree& state);
  ~TreeViewLabel() override;

  bool isSelected();
  void paint(Graphics& g) override;

  void valueTreePropertyChanged(ValueTree&,
                                const Identifier& property) override;

private:
  StorybookGroup::Child m_value;
  ValueTree& m_state;
};

} // namespace juce_visual_regressions
