# CutchEdit

A tool to manage Settings and Sample files for the WMD Clutch

Windows and macOS builds available at: https://cpr2323.github.io/clutchedit/index.html

Currently requires JUCE version 7. The revision from 1/10/2024: 31dfb05ea3299176a416bf9258e030d04a099798

# Windows

There are no special steps to installing on Windows.

# OSX

Since the application is not signed (I don't want to pay the $99/yr) you will have to do a manual step in the console to allow it to run.

1. Download A8Manager.zip, the app will be automatically extracted during download.
2. Use the following command to allow it to run
3. **_xattr -d com.apple.quarantine ~/Downloads/ClutchEdit.app_**
4. You can now run it. You can move it to the Applications folder if you do desire.

# Linux

There is no Linux version yet, but since we are using JUCE it should be _relative simple_.
