#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include"cocos2d.h"

USING_NS_CC;

class PauseScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();

	virtual bool init();

	void buttonPauseCallback(cocos2d::Ref *sender);

	void buttonSettingCallback(cocos2d::Ref *sender);
	CREATE_FUNC(PauseScene);
private:
	Size screenSize;
};


#endif
