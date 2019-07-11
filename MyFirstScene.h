#ifndef __MYFIRST_SCENE_h__
#define __MYFIRST_SCENE_h__


#include"cocos2d.h"
#include"ui/CocosGUI.h"
#define SCROLLING_BACKGROUND 0.005

USING_NS_CC;

class MyFirstScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene(); //Tao ra mot canh moi

	virtual bool init(); //khoi tao doi tuong cua lop MyFirstScene

	bool onTouchBegan(Touch *touch, Event *unused_event);

	void onTouchMoved(Touch *touch, Event *unused_event);

	void update(float dt);

	void buttonPauseCallback(cocos2d::Ref *sender);

	//void onTouchEnded(Touch *touch, Event *unused_event);

	// keyboard

	//void MyFirstScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	//void MyFirstScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	CREATE_FUNC(MyFirstScene);

private:

	Sprite *spaceShip;
	Sprite *bullet;
	Sprite *bee;
	Sprite *fire;
	Sprite *background1;
	Sprite *background2;
	Sprite *background3;

	Size screenSize;

};




#endif // !__MYFIRSTSCENE_h__


