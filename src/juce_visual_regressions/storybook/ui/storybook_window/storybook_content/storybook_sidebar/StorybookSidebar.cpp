//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookSidebar.h"

namespace juce_visual_regressions {

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