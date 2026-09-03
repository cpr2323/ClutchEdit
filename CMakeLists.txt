cmake_minimum_required(VERSION 3.22)

project(ClutchEdit VERSION 1.2)

# Submodules must be initialised before building:
#   git submodule update --init --recursive
add_subdirectory(submodules/JUCE builds/JUCE)

# oolib is a plain source list rather than a library, because its files include
# <JuceHeader.h> and so have to be compiled as part of a JUCE target. It defines
# OOLIB_SOURCES and OOLIB_INCLUDE_DIR.
include(submodules/oolib/oolib.cmake)

# The Projucer project had no company name, which left ProjectInfo::companyName
# empty and put the preferences directory directly under the user application
# data directory. JUCE's CMake support defaults the company to "yourcompany", so
# it is blanked here to keep the app reading its existing preferences file.
set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY JUCE_COMPANY_NAME "")

juce_add_gui_app(ClutchEdit
    PRODUCT_NAME "ClutchEdit"
    # Derived from the (now empty) company name it would come out as
    # "com..ClutchEdit", so it is spelled out to match the Projucer's version.
    BUNDLE_ID    "com.yourcompany.ClutchEdit"
    ICON_BIG     "Source/GUI/Clutch/Data/clutchediticon.png"
    ICON_SMALL   "Source/GUI/Clutch/Data/clutchediticon.png")

# The sources include <JuceHeader.h> rather than the individual module headers,
# so the header the Projucer used to generate is still needed.
juce_generate_juce_header(ClutchEdit)

# Without this, Visual Studio opens with ALL_BUILD selected and F5 fails with
# "Unable to start program ... ALL_BUILD. Access is denied." — ALL_BUILD is a
# utility target with nothing to launch.
set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT ClutchEdit)

set(SOURCE_FILES
    Source/AppProperties.cpp
    Source/AppProperties.h
    Source/Main.cpp)

set(CLUTCH_FILES
    Source/Clutch/BankListProperties.cpp
    Source/Clutch/BankListProperties.h
    Source/Clutch/BankProperties.cpp
    Source/Clutch/BankProperties.h
    Source/Clutch/ClutchProperties.cpp
    Source/Clutch/ClutchProperties.h
    Source/Clutch/EffectListProperties.cpp
    Source/Clutch/EffectListProperties.h
    Source/Clutch/EffectProperties.cpp
    Source/Clutch/EffectProperties.h
    Source/Clutch/HiHatIniData.cpp
    Source/Clutch/HiHatIniData.h
    Source/Clutch/HiHatIniKeys.h
    Source/Clutch/HiHatIniValues.h
    Source/Clutch/LedColorList.cpp
    Source/Clutch/LedColorList.h
    Source/Clutch/PatternListProperties.cpp
    Source/Clutch/PatternListProperties.h
    Source/Clutch/PatternProperties.cpp
    Source/Clutch/PatternProperties.h
    Source/Clutch/ProjectManager.cpp
    Source/Clutch/ProjectManager.h
    Source/Clutch/ProjectManagerProperties.cpp
    Source/Clutch/ProjectManagerProperties.h
    Source/Clutch/SamplePairProperties.cpp
    Source/Clutch/SamplePairProperties.h
    Source/Clutch/SampleProperties.cpp
    Source/Clutch/SampleProperties.h
    Source/Clutch/SettingsProperties.cpp
    Source/Clutch/SettingsProperties.h)

set(CLUTCH_AUDIO_FILES
    Source/Clutch/Audio/AudioPlayer.cpp
    Source/Clutch/Audio/AudioPlayer.h
    Source/Clutch/Audio/AudioPlayerProperties.cpp
    Source/Clutch/Audio/AudioPlayerProperties.h
    Source/Clutch/Audio/AudioSettingsProperties.cpp
    Source/Clutch/Audio/AudioSettingsProperties.h)

set(CLUTCH_DATA_FILES
    Source/Clutch/Data/HIHAT.INI)

set(GUI_FILES
    Source/GUI/CurrentFolderComponent.cpp
    Source/GUI/CurrentFolderComponent.h
    Source/GUI/GuiControlProperties.cpp
    Source/GUI/GuiControlProperties.h
    Source/GUI/GuiProperties.cpp
    Source/GUI/GuiProperties.h
    Source/GUI/MainComponent.cpp
    Source/GUI/MainComponent.h)

set(GUI_CLUTCH_FILES
    Source/GUI/Clutch/ClutchEditorComponent.cpp
    Source/GUI/Clutch/ClutchEditorComponent.h
    Source/GUI/Clutch/EffectEditorComponent.cpp
    Source/GUI/Clutch/EffectEditorComponent.h
    Source/GUI/Clutch/PatternEditorComponent.cpp
    Source/GUI/Clutch/PatternEditorComponent.h
    Source/GUI/Clutch/PatternListEditorComponent.cpp
    Source/GUI/Clutch/PatternListEditorComponent.h
    Source/GUI/Clutch/SampleBankComponent.cpp
    Source/GUI/Clutch/SampleBankComponent.h
    Source/GUI/Clutch/SampleManagerComponent.cpp
    Source/GUI/Clutch/SampleManagerComponent.h
    Source/GUI/Clutch/SettingsEditorComponent.cpp
    Source/GUI/Clutch/SettingsEditorComponent.h)

set(GUI_CLUTCH_DATA_FILES
    Source/GUI/Clutch/Data/clutchediticon.png)

# libsamplerate.c is a single translation unit that #includes the library's own
# .c files, so it is the only file from that tree that gets compiled.
set(SRC_FILES
    Source/SRC/libsamplerate.c
    Source/SRC/libsamplerate-0.1.9/src/samplerate.h)

# The files the Projucer marked resource="1". They are built into a separate
# binary data target, but stay listed in the groups above so the IDE tree still
# shows them next to the code they belong with.
set(RESOURCE_FILES
    ${CLUTCH_DATA_FILES}
    ${GUI_CLUTCH_DATA_FILES})

set_source_files_properties(${RESOURCE_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

juce_add_binary_data(ClutchEditBinaryData SOURCES ${RESOURCE_FILES})

source_group("Source"                 FILES ${SOURCE_FILES})
source_group("Source/Clutch"          FILES ${CLUTCH_FILES})
source_group("Source/Clutch/Audio"    FILES ${CLUTCH_AUDIO_FILES})
source_group("Source/Clutch/Data"     FILES ${CLUTCH_DATA_FILES})
source_group("Source/GUI"             FILES ${GUI_FILES})
source_group("Source/GUI/Clutch"      FILES ${GUI_CLUTCH_FILES})
source_group("Source/GUI/Clutch/Data" FILES ${GUI_CLUTCH_DATA_FILES})
source_group("Source/SRC"             FILES ${SRC_FILES})
# TREE keeps the IDE tree matching oolib's own Category folders
source_group(TREE ${OOLIB_INCLUDE_DIR}/oolib PREFIX "oolib" FILES ${OOLIB_SOURCES})

target_sources(ClutchEdit
    PRIVATE
        ${SOURCE_FILES}
        ${CLUTCH_FILES}
        ${CLUTCH_AUDIO_FILES}
        ${CLUTCH_DATA_FILES}
        ${GUI_FILES}
        ${GUI_CLUTCH_FILES}
        ${GUI_CLUTCH_DATA_FILES}
        ${SRC_FILES}
        ${OOLIB_SOURCES})

# oolib's files include each other as "oolib/<Category>/<File>.h", and so does the
# code here that uses them.
target_include_directories(ClutchEdit
    PRIVATE
        ${OOLIB_INCLUDE_DIR})

target_compile_definitions(ClutchEdit
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_STRICT_REFCOUNTEDPOINTER=1
        DONT_SET_USING_JUCE_NAMESPACE=1)

target_link_libraries(ClutchEdit
    PRIVATE
        ClutchEditBinaryData
        juce::juce_audio_processors_headless
        juce::juce_audio_utils
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
