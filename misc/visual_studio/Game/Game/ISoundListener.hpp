#pragma once
#ifndef ISoundListener_hpp
#define ISoundListener_hpp
#include <string>

class ISoundListener {
public:
	virtual ~ISoundListener() {}
	virtual void start(std::string address) = 0;
	virtual void pause() = 0;
	virtual void play() = 0;
	virtual void playEffect(int command) = 0;
protected:
	//static const int SOME_EFFECT = 0; 
};

#endif /* ISoundListener_hpp */