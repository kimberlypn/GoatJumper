#pragma once
#ifndef IKeyListener_hpp
#define IKeyListener_hpp

class IKeyListener {
public:
    // Virtual destructor
    virtual ~IKeyListener() {}
    // Handles the key event
    virtual void handleKey(int key) = 0;
    
    // Static constants corresponding to various key events
    static const int UP_ARROW = 0;
    static const int LEFT_ARROW = 1;
    static const int RIGHT_ARROW = 2;
    static const int EXIT = 3;
    static const int RESET = 4;
};

#endif /* IKeyListener_hpp */


