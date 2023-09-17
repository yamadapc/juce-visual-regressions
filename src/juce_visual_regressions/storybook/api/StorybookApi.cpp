//
// Created by Pedro Tacla Yamada on 17/9/2023.
//

#include "StorybookApi.h"

namespace juce_visual_regressions {

void story(std::string name, std::function<Component*()> block) {
  auto story = std::make_shared<StorybookStory>(name, block);
  StorybookRegistry::getInstance().getRootGroup()->addStory(story);
}

} // namespace juce_visual_regressions