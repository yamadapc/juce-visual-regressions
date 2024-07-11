#pragma once

#include <functional>
#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>

namespace juce_visual_regressions {

using namespace juce;

/**
 * Test if a component matches its disk snapshot golden image.
 *
 * Writes the `current` and `stable` images to disk as well as `diff` images.
 *
 * Images are written to:
 *
 * - `$projectRoot`/test/visual-regression/current
 * - `$projectRoot`/test/visual-regression/stable
 * - `$projectRoot`/test/visual-regression/diff
 *
 * Directories. Only the `stable` files are kept, which are considered to be the
 * golden images to test against.
 *
 * On any run, images will be written into the current directory and compared
 * with the images on the stable directory. Differences will be written into
 * diff. If the images match, the current/diff directories will be cleaned-up.
 *
 * Alternatively, if the stable image does not exist, the current image will be
 * moved to the stable directory.
 */
void matchesSnapshot(Component& component, std::string_view name);

/**
 * Run a snapshot test within a certain closure. This just set-ups the JUCE
 * message manager so that we can render the component into an image.
 */
void testComponent(const std::function<void()>& test);

/**
 * Run component snapshot test with a name and a closure that returns a
 * component pointer.
 */
void runComponentSnapshotTest(std::string_view name,
                              std::function<std::unique_ptr<Component>()> test);

/**
 * A component snapshot image.
 */
struct Snapshot {
  juce::Image image;
};

/**
 * Helper class for taking snapshots.
 */
class SnapshotTester {
public:
  SnapshotTester() = default;

  static Snapshot takeSnapshot(juce::Component& component);
};

} // namespace juce_visual_regressions