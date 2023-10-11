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
* `imagemagick`

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
  - This uses imagemagick, with a 5% pixel diff threshold and a 5s timeout
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

_TODO_

# License

MIT license - 2023 Pedro Tacla Yamada