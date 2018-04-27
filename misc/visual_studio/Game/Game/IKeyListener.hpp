#pragma once
#ifndef IKeyListener_hpp
#define IKeyListener_hpp

class IKeyListener {
public:
	virtual ~IKeyListener() {}
	virtual void handleKey(int key) = 0;

	static const int UP_ARROW = 0;
	static const int LEFT_ARROW = 1;
	static const int RIGHT_ARROW = 2;
	static const int EXIT = 3;
};

#endif /* IKeyListener_hpp */