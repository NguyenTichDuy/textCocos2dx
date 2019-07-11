#ifndef __SETTINGSCENE_H__
#define __SETTINGSCENE_H__

#include"cocos2d.h"

USING_NS_CC;

class SettingScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();

	virtual bool init();

	CREATE_FUNC(SettingScene);

private:
	Size screenSize;
	Size origin;
};



#endif //__SETTINGSCENE_H__

