#include"MyFirstScene.h"
#include"PauseScene.h"
#include"StartScene.h"
bool check = NULL;

cocos2d::Scene * MyFirstScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MyFirstScene::create();

	scene->addChild(layer);
	return scene;
}


auto origin = Director::getInstance()->getVisibleOrigin();

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MyFirstScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	screenSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();


	// Add background
	background1 = Sprite::create("BG.png");
	background2 = Sprite::create("BG1.png");
	background3 = Sprite::create("BG2.png");

	if (background1 == nullptr || background2 == nullptr || background3 == nullptr)
	{
		problemLoading("'BG.png'");
	}
	else
	{
		//add background1
		background1->setAnchorPoint(Vec2(0, 0));
		background1->setPosition(Vec2(0, 0));
		background1->setScale(screenSize.width / background1->getContentSize().width,
			screenSize.height / background1->getContentSize().height);	
		this->addChild(background1, -10);

		//add background2
		background2->setAnchorPoint(Vec2(0, 0));
		background2->setPosition(Vec2(screenSize.width, 0));
		background2->setScale(screenSize.width / background1->getContentSize().width,
			screenSize.height / background1->getContentSize().height);
		this->addChild(background2, -10);

		//add background3
		background3->setAnchorPoint(Vec2(0, 0));
		background3->setPosition(Vec2(screenSize.width * 2, 0));
		background3->setScale(screenSize.width / background1->getContentSize().width,
			screenSize.height / background1->getContentSize().height);
		this->addChild(background3, -10);
	}
	// update background
	this->update(10);
	this->scheduleUpdate();

	// Add button pause

	auto buttonPause = ui::Button::create("pause_norrmal.png", "pause_pressed.png");

	buttonPause->setPosition(Vec2(screenSize.width - buttonPause->getContentSize().width, buttonPause->getContentSize().height));

	buttonPause->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			buttonPauseCallback(sender);
			break;
		default:
			break;
		}
	});
	this->addChild(buttonPause, 2);

	// Add button resume
	//auto buttonResume = ui::Button::create("resume_normal.png", "resume_pressed.png");

	//buttonPause->setPosition(Vec2(screenSize.width - buttonPause->getContentSize().width, buttonPause->getContentSize().height));
	//buttonResume->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type)
	//{
	//	switch (type)
	//	{
	//	case cocos2d::ui::Widget::TouchEventType::BEGAN:
	//		break;
	//	case cocos2d::ui::Widget::TouchEventType::ENDED:

	//		break;
	//	default:
	//		break;
	//	}
	//});

	// Add space ship
	spaceShip = Sprite::create("spaceship.png");
	if (spaceShip == nullptr)
	{
		problemLoading("'bullet.png'");
	}
	else
	{
		spaceShip->setPosition(Vec2(screenSize.width / 4 +
			origin.x, screenSize.height / 2 + origin.y));
		spaceShip->setScale(0.5);
		spaceShip->setRotation(90);
		this->addChild(spaceShip, 1);
	}
	// add fire for bee
	const int numberFire = 9;

	fire = Sprite::create("Sprite_Fire_Shots_Flame_000.png");

	if (fire == nullptr)
	{
		problemLoading("'Sprite_Fire_Shots_Flame_000.png'");
	}
	else
	{
		//fire->setPosition(bee->getPositionX() + bee->getContentSize().width, bee->getPositionY());
		this->addChild(fire);

		fire->setRotation(90);
	

		Vector<SpriteFrame *> animaFire;

		animaFire.reserve(numberFire);

		animaFire.pushBack(SpriteFrame::create("Sprite_Fire_Shots_Flame_001.png",
			Rect(0, 0, fire->getContentSize().width, fire->getContentSize().height)));
		animaFire.pushBack(SpriteFrame::create("Sprite_Fire_Shots_Flame_002.png",
			Rect(0, 0, fire->getContentSize().width, fire->getContentSize().height)));
		animaFire.pushBack(SpriteFrame::create("Sprite_Fire_Shots_Flame_003.png",
			Rect(0, 0, fire->getContentSize().width, fire->getContentSize().height)));
		animaFire.pushBack(SpriteFrame::create("Sprite_Fire_Shots_Flame_004.png",
			Rect(0, 0, fire->getContentSize().width, fire->getContentSize().height)));
		animaFire.pushBack(SpriteFrame::create("Sprite_Fire_Shots_Flame_005.png",
			Rect(0, 0, fire->getContentSize().width, fire->getContentSize().height)));
		animaFire.pushBack(SpriteFrame::create("Sprite_Fire_Shots_Flame_006.png",
			Rect(0, 0, fire->getContentSize().width, fire->getContentSize().height)));
		animaFire.pushBack(SpriteFrame::create("Sprite_Fire_Shots_Flame_007.png",
			Rect(0, 0, fire->getContentSize().width, fire->getContentSize().height)));
		animaFire.pushBack(SpriteFrame::create("Sprite_Fire_Shots_Flame_008.png",
			Rect(0, 0, fire->getContentSize().width, fire->getContentSize().height)));
		animaFire.pushBack(SpriteFrame::create("Sprite_Fire_Shots_Flame_009.png",
			Rect(0, 0, fire->getContentSize().width, fire->getContentSize().height)));

		Animation * animationFire = Animation::createWithSpriteFrames(animaFire, 0.1);
		Animate *animaOfFire = Animate::create(animationFire);

		fire->runAction(RepeatForever::create(animaOfFire));
	}
	// add bee 
	const int numberSprite = 4;

	bee = Sprite::create("bee1.png");


	bee->setPosition(Vec2(spaceShip->getPosition().x - spaceShip->getContentSize().width / 2,
		spaceShip->getPosition().y + spaceShip->getContentSize().width / 2));
	bee->setRotation(90);
	bee->setScale(0.3);

	this->addChild(bee, 1);
	Vector<SpriteFrame *> animaBee;

	animaBee.reserve(numberSprite);

	animaBee.pushBack(SpriteFrame::create("bee1.png", Rect(0, 0, bee->getContentSize().width, bee->getContentSize().height)));
	animaBee.pushBack(SpriteFrame::create("bee2.png", Rect(0, 0, bee->getContentSize().width, bee->getContentSize().height)));
	animaBee.pushBack(SpriteFrame::create("bee3.png", Rect(0, 0, bee->getContentSize().width, bee->getContentSize().height)));

	Animation* animation = Animation::createWithSpriteFrames(animaBee, 0.1);
	Animate* animate = Animate::create(animation);

	bee->runAction(RepeatForever::create(animate));
	
	// add a touch event
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(MyFirstScene::onTouchBegan, this);

	listener->onTouchMoved = CC_CALLBACK_2(MyFirstScene::onTouchMoved, this);

	listener->onTouchEnded = CC_CALLBACK_2(MyFirstScene::onTouchEnded, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, spaceShip);

	return true;
}

bool MyFirstScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	Vec2 touchLocation = touch->getLocation();

	return true;
}

void MyFirstScene::onTouchMoved(Touch * touch, Event * unused_event)
{
	Vec2 touchLocation = touch->getLocation();

	spaceShip->setPosition(touchLocation.x, touchLocation.y);

	// add bee
	bee->setPosition(Vec2(spaceShip->getPosition().x - spaceShip->getContentSize().width / 2,
		spaceShip->getPosition().y + spaceShip->getContentSize().height / 2));
	//add bullet for bee
	fire->setPosition(Vec2(bee->getPositionX() + bee->getContentSize().width / 16, bee->getPositionY() + spaceShip->getContentSize().height + bee->getContentSize().width /8 ));

	//add bullet

	bullet = Sprite::create("bullet.png");

	bullet->setPosition(spaceShip->getPosition().x + bullet->getContentSize().width, spaceShip->getPosition().y);
	bullet->setRotation(90);

	this->addChild(bullet, 2);

	auto fired = MoveTo::create(0.5, Vec2(screenSize.width + bullet->getContentSize().width, spaceShip->getPositionY()));

	bullet->runAction(fired);
	if (bullet->getPositionX() >= screenSize.width)
	{
		bullet->cleanup();
	}
}
void MyFirstScene::update(float dt)
{
	background1->setPositionX(background1->getPositionX() - (SCROLLING_BACKGROUND * screenSize.width));
	background2->setPositionX(background2->getPositionX() - (SCROLLING_BACKGROUND * screenSize.width));
	background3->setPositionX(background3->getPositionX() - (SCROLLING_BACKGROUND * screenSize.width));

	if (background1->getPositionX() <= -screenSize.width)
	{
		background1->setPositionX(background3->getPositionX() + screenSize.width);
	}
	if (background2->getPositionX() <= -screenSize.width)
	{
		background2->setPositionX(background1->getPositionX() + screenSize.width);
	}
	if (background3->getPositionX() <= -screenSize.width)
	{
		background3->setPositionX(background2->getPositionX() + screenSize.width);
	}
}
void MyFirstScene::buttonPauseCallback(cocos2d::Ref * sender)
{
	Director::getInstance()->pushScene(PauseScene::createScene());
}
//void MyFirstScene::onTouchEnded(Touch *touch, Event *event)
//{
//	fire->release();
//}



