#!/bin/sh

# Same as buildpack.sh, but in the end creates a mac application bundle.
# First, install these tools:
#     brew install dylibbundler create-dmg
#
# Does not need user input. When the Finder ZeldaClassic.app -> Applications window opens
# don't do anything - just wait.

src="../.."
out="${src}/output"
nb="${out}/_auto/buildpack"
mac_nb="${out}/_auto/zelda-classic-mac"
rel="${src}/build/Release"

sh buildpack.sh "$rel"
set -eu

# Need shared libraries.
find "$rel" -name "*.dylib" -exec cp {} "$nb" \;

# Change some defaults.
sed -i -e 's/fullscreen = 0/fullscreen = 1/' "$nb/zquest.cfg"
sed -i -e 's/fullscreen = 0/fullscreen = 1/' "$nb/zc.cfg"
find "$nb" -name "*.cfg-e" -exec rm {} \;

# Delete things Mac build won't need.
# TODO: better system for defining what files are bundled for each platform.
find "$nb" -name "*.exe" -exec rm {} \;
find "$nb" -name "*.dll" -exec rm {} \;
rm -rf "$nb/Addons"
rm -rf "$nb/utilities"

# Set SKIP_APP_BUNDLE=1 to skip building an osx application bundle.
# This won't be able to distribute easily, because OSX will prevent users from running
# unverified binaries unless they right-click->Open and ignore a scary warning. Even then,
# when zlauncher/zquest opens other ZC processes OSX will prevent it without a way to ignore
# the intervention, so some features won't work.
if test "${SKIP_APP_BUNDLE+x}"; then
  rm -rf "$mac_nb"
  mv "$nb" "$mac_nb"
  echo "Done"
  exit
fi

# Prepare the Mac application bundle.
contents="$mac_nb/ZeldaClassic.app/Contents"

rm -rf "$mac_nb"
mkdir -p "$contents/MacOS"
cp Info.plist "$contents"
mv buildpack/zlauncher "$contents/MacOS"
mv buildpack "$contents/Resources"

# Generate icon.
ICONDIR="$contents/Resources/icons.iconset"
ICON=../zc.png

mkdir "$ICONDIR"

# Normal screen icons
for size in 16 32 64 128 256 512; do
sips -z $size $size $ICON --out $ICONDIR/icon_${size}x${size}.png ;
done

# Retina display icons
for size in 32 64 256 512; do
sips -z $size $size $ICON --out "$ICONDIR"/icon_$(expr $size / 2)x$(expr $size / 2)x2.png ;
done

# Make a multi-resolution Icon
iconutil -c icns -o "$contents/Resources/icons.icns" "$ICONDIR"
rm -rf "$ICONDIR"

# Move shared libraries out of bundle (to be re-placed by dylibbundler)
tmp_libs_dir="$mac_nb/libs"
mkdir -p "$tmp_libs_dir"
find "$contents/Resources" -name "*.dylib" -exec mv {} "$tmp_libs_dir" \;

# Correct the library paths in the executable, and codesign.
dylibbundler -od -b -d "$contents/libs/" -s "$tmp_libs_dir" \
    -x "$contents/MacOS/zlauncher" -x "$contents/Resources/zquest" \
    -x "$contents/Resources/zelda" -x "$contents/Resources/zscript"
rm -rf "$tmp_libs_dir"

rm -f "ZeldaClassic.dmg"
create-dmg \
  --volname "ZeldaClassic" \
  --volicon "$contents/Resources/icons.icns" \
  --window-pos 200 120 \
  --window-size 800 400 \
  --icon-size 100 \
  --icon "ZeldaClassic.app" 200 190 \
  --hide-extension "ZeldaClassic.app" \
  --app-drop-link 600 185 \
  "ZeldaClassic.dmg" \
  "$mac_nb"

echo "Done!"
