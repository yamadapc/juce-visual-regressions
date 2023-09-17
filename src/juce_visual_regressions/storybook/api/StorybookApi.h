//
// Created by Pedro Tacla Yamada on 20/8/2023.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include <utility>

#include "../model/StorybookRegistry.h"

namespace juce_visual_regressions {

using namespace juce;

void story(std::string name, std::function<Component*()> block);

struct StoryDecl {
  StoryDecl(std::string name, std::function<Component*()> block) {
    story(std::move(name), block);
  }
};

#define STORY_IMPL(block_name, name)                                           \
  static juce::Component* block_name();                                        \
  const juce_visual_regressions::StoryDecl STORY_UNIQUE_NAME(autoRegister)(    \
    name, &block_name);                                                        \
  static juce::Component* block_name()

#define STORY_UNIQUE_NAME_IMPL2(name, part) name##part
#define STORY_UNIQUE_NAME_IMPL(name, part) STORY_UNIQUE_NAME_IMPL2(name, part)
#define STORY_UNIQUE_NAME(name) STORY_UNIQUE_NAME_IMPL(name, __COUNTER__)

#define STORY(name) STORY_IMPL(STORY_UNIQUE_NAME(Story), name)

} // namespace juce_visual_regressions
