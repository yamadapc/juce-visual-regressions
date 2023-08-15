#include <fmt/core.h>

#include <juce_gui_basics/juce_gui_basics.h>

Optional<File> getRootProjectDirectory (const File& file)
{
    File current = file;
    while (current != current.getParentDirectory ())
    {
        if (current.getChildFile (".clang-format").exists ())
            return current;
        current = current.getParentDirectory ();
    }
    return nullopt;
}

void matchesSnapshot (Component& component, std::string_view name)
{
    auto rootDirectory =
        *getRootProjectDirectory (File::getCurrentWorkingDirectory ());
    auto image =
        component.createComponentSnapshot (component.getBounds (), false, 1.0f);

    // juce Image to file

    const File& filePath = rootDirectory.getChildFile (
        fmt::format ("./test/visual-regression/current/{}.png", name));
    filePath.getParentDirectory ().createDirectory ();
    filePath.deleteFile ();
    File file (filePath);
    auto fileOutputStream = file.createOutputStream ();
    if (fileOutputStream == nullptr)
        throw std::runtime_error ("Could not create file output stream");
    PNGImageFormat png;
    png.writeImageToStream (image, *fileOutputStream);
}

void testComponent (const std::function<void ()>& test)
{
    MessageManager::getInstance ();
    MessageManagerLock messageManagerLock;
    assert (messageManagerLock.lockWasGained ());

    test ();

    juce::DeletedAtShutdown::deleteAll ();
    juce::MessageManager::deleteInstance ();
}

struct Snapshot
{
    juce::Image image;
};

class SnapshotTester
{
public:
    SnapshotTester () = default;

    Snapshot takeSnapshot (juce::Component& component)
    {
        auto image = component.createComponentSnapshot (
            component.getLocalBounds (), true);
        Snapshot snapshot = {std::move (image)};
        return snapshot;
    }
};