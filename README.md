# juce-visual-regressions

> **THIS IS PRE-ALPHA SOFTWARE IN DEVELOPMENT**

`juce-visual-regressions` provide a barebones mechanism for:

* Creating "Storybooks" of JUCE components for integration testing and
  explorative UI development
* Writing "visual regression" tests

![](storybook_screenshot.png)

## Requirements

* JUCE
* C++ compiler

## Rationale

Visual regression tests can be used to guarantee UI consistency across platforms, window sizes and resilient to code
and dependency changes. The idea is to set-up test-suites that will render UI components into images and then compare
them with previous versions.

If there's a difference, the developer making changes can update the "current image", effectively ignoring the failure.

The recommendation would be that these images be stored in GIT using GIT-LFS. This makes it easy to review visual
changes together with code changes during the code review process.

## VR Testing - Usage

With Catch2 as an example.

`runComponentSnapshotTest` will:
* Set-up message manager
* Create the component using the provided factory function
* Take a snapshot of the component
* Write the snapshot to `$PROJECT_ROOT/test/visual-regressions/current/$NAME.png`
  - $PROJECT_ROOT is found by looking for .git, in the future this can be configurable
* Compare the snapshot with the snapshot at `$PROJECT_ROOT/test/visual-regressions/stable/$NAME.png` if it exists
  - Write the diff to `$PROJECT_ROOT/test/visual-regressions/diff/$NAME.png`
  - This uses a 5% pixel diff threshold
* Fail the test (throw an exception) if the diff command fails
* Delete the component and update the stored snapshot

```c++
TEST_CASE ("PresetSearchInput")
{
    juce_visual_regressions::runComponentSnapshotTest (
        "PresetSearchInput__EmptyState",
        [&] ()
        {
            auto* presetSearchInput = new PresetSearchInput ();
            presetSearchInput->setSize (1000, 30);
            presetSearchInput->setLookAndFeel (CustomLookAndFeel::instance ());
            return presetSearchInput;
        });

    juce_visual_regressions::runComponentSnapshotTest (
        "PresetSearchInput__NonEmptyState",
        [&] ()
        {
            auto* presetSearchInput = new PresetSearchInput ();
            presetSearchInput->setSize (1000, 30);
            presetSearchInput->getTextEditor ().setText ("long");
            presetSearchInput->setLookAndFeel (CustomLookAndFeel::instance ());
            return presetSearchInput;
        });
}
```

### Updating snapshots

To update the stored snapshot, delete the current snapshot.

## Storybook Usage

### CMake set-up
To setup the Storybook app target, use the exported CMake function, this section assumes you have a `MyPlugin` JUCE
plugin setup and that `PLUGIN_INCLUDES`, `PLUGIN_SOURCES` and `PLUGIN_DEFINITIONS` are set and relevant.

```cmake
# ==============================================================================
# Storybook
# ==============================================================================
juce_vr_add_storybook(MyPluginStorybook)
target_sources(MyPluginStorybook PRIVATE ${PLUGIN_SOURCES})
get_target_property(juce_library_code MyPlugin JUCE_GENERATED_SOURCES_DIRECTORY)
message(STATUS "juce_library_code: ${juce_library_code}")
target_include_directories(MyPluginStorybook PRIVATE ${PLUGIN_INCLUDES} ${juce_library_code})
target_link_libraries(
  MyPluginStorybook PRIVATE
  juce::juce_audio_utils
  juce_visual_regressions
  # focusrite-e2e::focusrite-e2e
)
target_compile_definitions(MyPluginStorybook PRIVATE ${PLUGIN_DEFINITIONS})
```

### Source code usage

The storybook target will set `JUCE_VR_IS_STORYBOOK` to 1, so you can use that to conditionally include some stories:
```c++
class InputMuter : public Component {
    // ...
};

#if JUCE_VR_IS_STORYBOOK
#include <juce_visual_regressions/juce_visual_regressions.h>

STORY ("InputMeter")
{
    return new InputMeter ();
}
#endif
```

This API is subject to change. By doing this, when running the storybook you'll see a menu item "InputMeter" that
renders your `InputMeter` component when clicked.

# License

MIT license - 2023 Pedro Tacla Yamada

JUCE has its own license.