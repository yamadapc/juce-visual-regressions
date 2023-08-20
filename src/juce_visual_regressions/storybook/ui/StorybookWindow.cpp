//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#include "StorybookWindow.h"

#include <utility>

namespace juce_visual_regressions {

StorybookWindow::StorybookWindow(StorybookRegistry& storybookRegistry)
    : DocumentWindow("MainWindow", Colours::white, DocumentWindow::allButtons),
      m_storybookRegistry(storybookRegistry),
      m_storybookContent(m_storybookRegistry) {
  setSize(500, 500);
  setUsingNativeTitleBar(true);
  setCentrePosition(getParentMonitorArea().getCentre());
  setResizable(true, false);

  setContentNonOwned(&m_storybookContent, false);
}

void StorybookWindow::closeButtonPressed() {
  JUCEApplicationBase::quit();
}

} // namespace juce_visual_regressions