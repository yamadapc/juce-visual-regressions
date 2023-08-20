//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include "StorybookWindow.h"
#include <juce_gui_basics/juce_gui_basics.h>

namespace juce_visual_regressions {

using namespace juce;

class StorybookApplication : public JUCEApplication {
public:
  StorybookApplication();

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StorybookApplication)

  const String getApplicationName() override;
  const String getApplicationVersion() override;
  void initialise(const String& commandLineParameters) override;
  void shutdown() override;

  StorybookRegistry& m_storybookRegistry;
  ValueTree m_state;
  std::unique_ptr<StorybookWindow> m_mainWindow;
};

} // namespace juce_visual_regressions
