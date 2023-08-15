#include "JuceHeader.h"
#include "SnapshotTester.h"

int main ()
{
    SnapshotTester tester;

    testComponent (
        [] ()
        {
            juce::TextButton component = juce::TextButton ("Hello World");
            component.setBounds ({0, 0, 100, 100});
            matchesSnapshot (component, "test");
        });

    return 0;
}