#pragma once
#ifndef IEffectListener_hpp
#define IEffectListener_hpp

class IEffectListener {
public:
	virtual ~IEffectListener() {}
	virtual void displayEffect(int command) = 0;
protected:
	//static const int SOME_EFFECT = 0; 
};

#endif /* IEffectListener_hpp */