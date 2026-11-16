# ripchord

Ripchord is a free MIDI plugin for Mac and PC that makes it easy to create, perform and remix chord progressions. The plugin manual and download can be found here: https://trackbout.com/ripchord

# open source

Ripchord is open source under the GNU General Public License v3.0. The license can be found here: https://github.com/trackbout/ripchord/blob/master/LICENSE

# building on Linux

Ripchord can be built on Linux (Standalone app and VST3 plugin) with CMake. JUCE 7.0.12 is downloaded automatically at configure time.

Install the build tools and JUCE's dependencies (Debian/Ubuntu names shown):

```
sudo apt install build-essential cmake ninja-build git pkg-config libasound2-dev libfreetype-dev \
  libx11-dev libxext-dev libxinerama-dev libxrandr-dev libxcursor-dev libxcomposite-dev \
  libgl1-mesa-dev libcurl4-openssl-dev libfontconfig1-dev
```

Then build:

```
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

The outputs are in `build/Ripchord_artefacts/Release/` (`Standalone/Ripchord` and `VST3/Ripchord.vst3`). Copy the `.vst3` folder to `~/.vst3/` to use it in a DAW. To reuse an existing JUCE checkout, pass `-DJUCE_DIR=/path/to/JUCE`.

Binaries link against the glibc of the machine they are built on, so build on the oldest distribution you want to support.
