#include "SnapshotTester.h"

namespace juce_visual_regressions {

constexpr std::array projectMarkerFiles = {
  ".clang-format",
  ".git",
};

Optional<File> getRootProjectDirectory(const File& file) {
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

void matchesSnapshot(Component& component, std::string_view name) {
  auto rootDirectory =
    *getRootProjectDirectory(File::getCurrentWorkingDirectory());
  auto image =
    component.createComponentSnapshot(component.getBounds(), false, 1.0f);

  // juce Image to file

  const File& filePath = rootDirectory.getChildFile(
    juce::String::formatted("./test/visual-regression/current/%s.png", name));
  filePath.getParentDirectory().createDirectory();
  filePath.deleteFile();
  File file(filePath);
  auto fileOutputStream = file.createOutputStream();
  if(fileOutputStream == nullptr)
    throw std::runtime_error("Could not create file output stream");
  PNGImageFormat png;
  png.writeImageToStream(image, *fileOutputStream);

  const File& previousFilePath = rootDirectory.getChildFile(
    juce::String::formatted("./test/visual-regression/stable/%s.png", name));
  previousFilePath.getParentDirectory().createDirectory();
  if(!previousFilePath.exists()) {
    filePath.moveFileTo(previousFilePath);
    return;
  }

  const File& diffFilePath = rootDirectory.getChildFile(
    juce::String::formatted("./test/visual-regression/diff/%s.png", name));
  diffFilePath.getParentDirectory().createDirectory();
  juce::ChildProcess diffProcess;
  diffProcess.start("magick compare -metric AE -fuzz 5% \"" +
                    previousFilePath.getFullPathName() + "\" \"" +
                    filePath.getFullPathName() + "\" \"" +
                    diffFilePath.getFullPathName() + "\"");

  assert(diffProcess.waitForProcessToFinish(5000));

  assert(diffProcess.getExitCode() == 0);
}

void testComponent(const std::function<void()>& test) {
  MessageManager::getInstance();
  MessageManagerLock messageManagerLock;
  assert(messageManagerLock.lockWasGained());

  test();

  juce::DeletedAtShutdown::deleteAll();
  juce::MessageManager::deleteInstance();
}

void runComponentSnapshotTest(std::string_view name,
                              std::function<Component*()> test) {
  testComponent([&]() {
    auto component = test();
    matchesSnapshot(*component, name);
    delete component;
  });
}

Snapshot SnapshotTester::takeSnapshot(Component& component) {
  auto image =
    component.createComponentSnapshot(component.getLocalBounds(), true);
  Snapshot snapshot = {std::move(image)};
  return snapshot;
}

} // namespace juce_visual_regressions