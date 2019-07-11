#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class StartScene :public cocos2d::Layer
{
public:
	static	cocos2d::Scene *createSecene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref *pSender);

	void menuStartCallback(cocos2d::Ref *pSender);

	CREATE_FUNC(StartScene);
};


#endif // !__START_SCENE_H__

