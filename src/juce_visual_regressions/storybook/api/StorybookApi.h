//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../model/StorybookRegistry.h"

namespace juce_visual_regressions {

using namespace juce;

void story(std::string name, std::shared_ptr<Component> component) {
  auto story = std::make_shared<StorybookStory>(name, component);
  StorybookRegistry::getInstance().getRootGroup()->addStory(story);
}

} // namespace juce_visual_regressions
