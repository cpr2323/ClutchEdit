
#include <JuceHeader.h>
#include "MainComponent.h"

enum class KeyType
{
    intType,
    floatType,
    stringType
};
struct Key
{
    juce::String keyName;
    KeyType keyType;
    juce::String defaultValue;
};

class ClutchEditApplication  : public juce::JUCEApplication
{
public:
    ClutchEditApplication() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    class ClutchData
    {
    public:
        ClutchData () = default;
        ~ClutchData () = default;

        void readFromFile (const juce::File& file)
        {
            juce::FileInputStream inputStream (file);
            if (inputStream.openedOk())
            {
                juce::String currentSection;
                while (!inputStream.isExhausted())
                {
                    juce::String line { inputStream.readNextLine () };
                    ClutchIniFileLine iniLine;
                    iniLine.section = currentSection;
                    iniLine.rawLine = line;
                    auto trimmedLine = line.trim ();
                    if (trimmedLine.isEmpty())
                    {
                        iniLine.lineType = LineType::unknown;
                    }
                    else if (trimmedLine.startsWithChar (';'))
                    {
                        iniLine.lineType = LineType::comment;
                    }
                    else if (trimmedLine.startsWithChar ('['))
                    {
                        iniLine.lineType = LineType::section;
                        currentSection = trimmedLine.fromFirstOccurrenceOf ("[", false, false).upToLastOccurrenceOf ("]", false, false).trim ();
                        iniLine.section = currentSection;
                    }
                    else
                    {
                        // PITCH_LOW                         = 0.125            ; Min pitch 0.001 to 0.5                                  d: 0.125
                        auto key { trimmedLine.upToFirstOccurrenceOf (" ", false, false).trim () };
                        if (! key.isEmpty())
                        {
                            auto afterKey = trimmedLine.fromFirstOccurrenceOf (" ", false, false).trim ();
                            if (afterKey.startsWithChar ('='))
                            {
                                auto valuePart = afterKey.fromFirstOccurrenceOf ("=", false, false).trim ();
                                if (! valuePart.isEmpty())
                                {
                                    iniLine.lineType = LineType::keyValuePair;
                                    iniLine.key = key;
                                    iniLine.value = valuePart.upToFirstOccurrenceOf (" ;", false, false).trim ();
                                    auto afterValue = valuePart.fromFirstOccurrenceOf (" ;", false, false).trim ();
                                    if (! afterValue.isEmpty())
                                    {
                                        auto defaultValueIndex = afterValue.lastIndexOf ("d:");
                                        if (defaultValueIndex != -1)
                                            iniLine.defaultValue = afterValue.substring (defaultValueIndex + 2).trim();
                                    }
                                }
                            }
                        }
                        else
                        {
                            iniLine.lineType = LineType::unknown;
                        }
                    }
                    iniLines.push_back (iniLine);
                }
            }
        }
    private:
        enum class LineType
        {
            unknown,
            comment,
            section,
            keyValuePair
        };
        struct ClutchIniFileLine
        {
            LineType lineType { LineType::unknown };
            juce::String section;
            juce::String key;
            juce::String value;
            juce::String defaultValue;
            juce::String rawLine;
        };
        std::vector<ClutchIniFileLine> iniLines;
    };

    void initialise (const juce::String& commandLine) override
    {
        ClutchData clutchData;
        clutchData.readFromFile (juce::File::getCurrentWorkingDirectory ().getChildFile("HIHAT.INI"));
        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION (ClutchEditApplication)
