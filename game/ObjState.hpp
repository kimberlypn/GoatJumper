#pragma once
#ifndef ObjState_hpp
#define ObjState_hpp

#include "Posn.hpp"
#include <string>
using namespace std;

// Structure used to encapsulate GameObj (physics-related) details
// so that the view does not need to know what a GameObj is
struct ObjState {
    // File source of the image to be rendered
    string imgSrc;
    // Position at which to render the image
    Posn coordinates;
    // Dimensions of the image
    int height;
    int width;
};

#endif /* ObjState_hpp */

