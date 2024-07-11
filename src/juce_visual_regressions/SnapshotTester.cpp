#include "SnapshotTester.h"
#include <cassert>

namespace juce_visual_regressions {

constexpr std::array projectMarkerFiles = {
  ".clang-format",
  ".git",
};

/**
 * Search for the project root directory given a file-path by walking up the
 * directory tree looking for either a .clang-format or .git file/directory.
 */
static Optional<File> getRootProjectDirectory(const File& file) {
  File current = file;
  while(current != current.getParentDirectory()) {
    for(auto& targetFile : projectMarkerFiles) {
      if(current.getChildFile(targetFile).exists()) {
        return current;
      }
    }

    current = current.getParentDirectory();
  }
  return nullopt;
}

/**
 * The result of comparing two images pixel by pixel.
 *
 * Ratio is the ratio of differing pixels.
 *
 * diffImage is an image with differing pixels highlighted in red.
 */
struct ImageComparisonResult {
  double ratio;
  Image diffImage;
};

/**
 * Compare two images pixel by pixel and return the `ImageComparisonResult`.
 */
static ImageComparisonResult compareImages(const Image& imageLeft,
                                           const Image& imageRight) {
  const auto height = std::max(imageLeft.getHeight(), imageRight.getHeight());
  const auto width = std::max(imageLeft.getWidth(), imageRight.getWidth());

  const auto totalPixels = height * width;
  auto matchingPixels = 0;

  auto diffImage = Image(Image::PixelFormat::RGB, width, height, true);

  for(auto y = 0; y < height; y += 1) {
    for(auto x = 0; x < width; x += 1) {
      auto pixelLeft = imageLeft.getPixelAt(x, y);
      auto pixelRight = imageRight.getPixelAt(x, y);

      if(pixelLeft != pixelRight) {
        matchingPixels += 1;
        diffImage.setPixelAt(x, y, Colours::red);
      } else {
        diffImage.setPixelAt(x, y, pixelLeft.withAlpha(0.5f));
      }
    }
  }

  return ImageComparisonResult{.ratio = static_cast<double>(matchingPixels) /
                                        static_cast<double>(totalPixels),
                               .diffImage = diffImage};
}

void matchesSnapshot(Component& component, std::string_view name) {
  auto rootDirectory =
    *getRootProjectDirectory(File::getCurrentWorkingDirectory());
  const File& filePath = rootDirectory.getChildFile(
    String::formatted("./test/visual-regression/current/%s.png", name));
  filePath.getParentDirectory().createDirectory();
  filePath.deleteFile();
  PNGImageFormat png;

  auto currentImage =
    component.createComponentSnapshot(component.getBounds(), false, 1.0f);
  {
    File file(filePath);
    auto fileOutputStream = file.createOutputStream();
    if(fileOutputStream == nullptr)
      throw std::runtime_error("Could not create file output stream");
    png.writeImageToStream(currentImage, *fileOutputStream);
  }

  const File& previousFilePath = rootDirectory.getChildFile(
    String::formatted("./test/visual-regression/stable/%s.png", name));
  previousFilePath.getParentDirectory().createDirectory();
  if(!previousFilePath.exists()) {
    filePath.moveFileTo(previousFilePath);
    return;
  }

  const File& diffFilePath = rootDirectory.getChildFile(
    String::formatted("./test/visual-regression/diff/%s.png", name));
  diffFilePath.getParentDirectory().createDirectory();

  const auto stableImage = ImageFileFormat::loadFrom(previousFilePath);

  auto result = compareImages(stableImage, currentImage);
  auto diffOutputStream = diffFilePath.createOutputStream();
  png.writeImageToStream(result.diffImage, *diffOutputStream);

  if(result.ratio > 0.05) {
    throw std::runtime_error("Diff was greater than 5%");
  }

  diffFilePath.deleteFile();
  filePath.deleteFile();
}

void testComponent(const std::function<void()>& test) {
  MessageManager::getInstance();
  MessageManagerLock messageManagerLock;
  assert(messageManagerLock.lockWasGained());

  test();

  DeletedAtShutdown::deleteAll();
  MessageManager::deleteInstance();
}

void runComponentSnapshotTest(
  std::string_view name,
  std::function<std::unique_ptr<Component>()> test) {
  testComponent([&]() {
    auto component = test();
    matchesSnapshot(*component, name);
  });
}

Snapshot SnapshotTester::takeSnapshot(Component& component) {
  auto image =
    component.createComponentSnapshot(component.getLocalBounds(), true);
  Snapshot snapshot = {std::move(image)};
  return snapshot;
}

} // namespace juce_visual_regressions