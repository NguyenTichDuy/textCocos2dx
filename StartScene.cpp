#include"StartScene.h"
#include "MyFirstScene.h"

cocos2d::Scene * StartScene::createSecene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();

	scene->addChild(layer);
	return scene;
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// add background
	auto background = Sprite::create("backgroundSpace.png");
	
	if (background == nullptr)
	{
		problemLoading("backgroundSpace.png");
	}
	else
	{
		background->setPosition(screenSize.width / 2 + origin.x, screenSize.height / 2 + origin.y);
		background->setScale(screenSize.width / background->getContentSize().width, screenSize.height / background->getContentSize().height);
		this->addChild(background, -10);
	}
	// add text field 
	auto myName = ui::TextField::create("Editing your name", "fonts/Marker Felt.ttf", 30);

	//myName->setPasswordEnabled(true);
	myName->setMaxLength(10);
	myName->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	myName->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type)
	{
		printf("editing your name\n");
	});

	this->addChild(myName, 1);
	// add logo space ship
	auto logo = Sprite::create("title.png");
	if (logo == nullptr)
	{
		problemLoading("'title.png'");
	}
	else
	{
		logo->setAnchorPoint(Vec2(0.5, 0));
		logo->setPosition(Vec2(screenSize.width / 2 + origin.x, screenSize.height - logo->getContentSize().height));
		this->addChild(logo, 1);
	}


	Vector<MenuItem *> menuItems;
	// add start item
	auto startItem = MenuItemImage::create(
		"play_normal.png",
		"play_press.png",
		CC_CALLBACK_1(StartScene::menuStartCallback, this));
	if (startItem == nullptr ||
		startItem->getContentSize().width <= 0 ||
		startItem->getContentSize().height <= 0)
	{
		problemLoading("'play_normal.png' and 'play_pressed.png'");
	}
	else
	{
		startItem->setPosition(screenSize.width / 2 + origin.x, screenSize.height / 3 + origin.y);
		startItem->setScale(0.5);
		menuItems.pushBack(startItem);

	}
	// add close item
	auto closeItem = MenuItemImage::create(
		"exit_normal.png",
		"exit_pressed.png",
		CC_CALLBACK_1(StartScene::menuCloseCallback, this));
	if (closeItem == nullptr)
	{
		problemLoading("'exit_normal.png' and 'exit_pressed.png'");
	}
	else
	{
		closeItem->setScale(0.2);
		closeItem->setPosition(screenSize.width / 2 + origin.x, screenSize.height / 3 - startItem->getContentSize().height /2);
		
		menuItems.pushBack(closeItem);
	}
	auto menu = Menu::createWithArray(menuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto gotoNext = CallFunc::create([]() {
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, MyFirstScene::createScene(), Color3B(255, 0, 255)));
	});
	
	return true;
}

void StartScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}

void StartScene::menuStartCallback(cocos2d::Ref * pSender)
{
	auto screenSize = Director::getInstance()->getVisibleSize();

	auto label = Label::createWithTTF("Let Start","fonts/Marker Felt.ttf", 32);
	
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		label->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2.3));
		label->setColor(Color3B::BLUE);
		label->enableGlow(Color4B::ORANGE);
		label->setOpacity(0);
		this->addChild(label, 1);
	}
	auto opacityIn = FadeIn::create(1);
	label->runAction(opacityIn);

	auto gotoNext = CallFunc::create([]()
	{
		Director::getInstance()->replaceScene(TransitionFade::create(2, MyFirstScene::createScene(), Color3B::BLACK));
	}
	);
	auto sequence = Sequence::create(DelayTime::create(2), gotoNext, nullptr);
	
	this->runAction(sequence);
}

