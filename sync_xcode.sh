#!/bin/bash

# Remove all .hpp files from game
find game -name "*.hpp" -type f -delete

# Remove all .cpp files from game
find game -name "*.cpp" -type f -delete

# Copy all .hpp files from misc/xcode/game/Game to game
find misc/xcode/game/Game -name \*.hpp -exec cp {} game \;

# Copy all .cpp files from misc/xcode/game/Game to game
find misc/xcode/game/Game -name \*.cpp -exec cp {} game \;

# Copy all assets to game
cp -r misc/xcode/game/Game/assets game/
