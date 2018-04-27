#!/bin/bash

# Remove all .hpp files from game
find game -name "*.hpp" -type f -delete

# Remove all .cpp files from game
find game -name "*.cpp" -type f -delete

# Copy all .hpp files from misc/visual_studio/Game/Game to game
find misc/visual_studio/Game/Game -name \*.hpp -exec cp {} game \;

# Copy all .cpp files from misc/visual_studio/Game/Game to game
find misc/visual_studio/Game/Game -name \*.cpp -exec cp {} game \;
