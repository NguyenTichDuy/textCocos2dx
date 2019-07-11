#include"SettingScene.h"

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

cocos2d::Scene *SettingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingScene::create();

	scene->addChild(layer);
	return scene;
}

bool SettingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	screenSize = Director::getInstance()->getVisibleSize();

	origin = Director::getInstance()->getVisibleOrigin();

	// add menu

	auto menuSprite = Sprite::create("Setting/Window.png");

	if (menuSprite == nullptr)
	{
		problemLoading("'Setting/Window.png'");
	}
	else
	{
		menuSprite->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
		menuSprite->setScale(screenSize.width / 3 / menuSprite->getContentSize().width,
			screenSize.height * 2 / 3 / menuSprite->getContentSize().height);

		this->addChild(menuSprite, -5);
	}
	// add slider
	


	return true;
}