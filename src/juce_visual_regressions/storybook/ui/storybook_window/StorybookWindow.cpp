//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookWindow.h"

#include <utility>

namespace juce_visual_regressions {

StorybookWindow::StorybookWindow(StorybookRegistry& storybookRegistry,
                                 ValueTree& state)
    : DocumentWindow("MainWindow", Colours::white, DocumentWindow::allButtons),
      m_storybookRegistry(storybookRegistry),
      m_storybookContent(m_storybookRegistry, state) {
  setSize(800, 500);
  setUsingNativeTitleBar(true);
  setCentrePosition(getParentMonitorArea().getCentre());
  setResizable(true, false);

  setContentNonOwned(&m_storybookContent, false);
}

void StorybookWindow::closeButtonPressed() {
  JUCEApplicationBase::quit();
}

} // namespace juce_visual_regressions