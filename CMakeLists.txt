cmake_minimum_required(VERSION 3.22)

project(Ripchord VERSION 2.7.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JUCE is fetched automatically; point JUCE_DIR at a local checkout to avoid the download.
set(JUCE_DIR "" CACHE PATH "Path to an existing JUCE checkout (optional)")

include(FetchContent)
if (JUCE_DIR)
    add_subdirectory(${JUCE_DIR} JUCE EXCLUDE_FROM_ALL)
else()
    FetchContent_Declare(JUCE
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 7.0.12
        GIT_SHALLOW ON)
    FetchContent_MakeAvailable(JUCE)
endif()

# Standalone + VST3 (AU is macOS-only)
set(RIPCHORD_FORMATS Standalone VST3)
if (APPLE)
    list(APPEND RIPCHORD_FORMATS AU)
endif()

juce_add_plugin(Ripchord
    COMPANY_NAME "Trackbout"
    COMPANY_WEBSITE "https://trackbout.com"
    PLUGIN_MANUFACTURER_CODE TkBt
    PLUGIN_CODE RpCh
    FORMATS ${RIPCHORD_FORMATS}
    PRODUCT_NAME "Ripchord"
    DESCRIPTION "Ripchord"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT TRUE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    AU_MAIN_TYPE kAudioUnitType_MusicDevice
    VST3_CATEGORIES Instrument Synth
    COPY_PLUGIN_AFTER_BUILD FALSE)

juce_generate_juce_header(Ripchord)

file(GLOB_RECURSE RIPCHORD_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
target_sources(Ripchord PRIVATE ${RIPCHORD_SOURCES})

# The SVG icons are loaded from BinaryData (see Source/Modules/Images.h)
file(GLOB RIPCHORD_ASSETS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/*.svg)
juce_add_binary_data(RipchordAssets SOURCES ${RIPCHORD_ASSETS})

# Sources include each other by bare filename, so every Source subfolder is an include dir
target_include_directories(Ripchord PRIVATE
    Source
    Source/Components
    Source/Messaging
    Source/Modules
    Source/Process)

target_compile_definitions(Ripchord PUBLIC
    JUCE_MODAL_LOOPS_PERMITTED=1
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_REPORT_APP_USAGE=0)

target_link_libraries(Ripchord
    PRIVATE
        RipchordAssets
        juce::juce_audio_utils
        juce::juce_cryptography
        juce::juce_opengl
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags)
