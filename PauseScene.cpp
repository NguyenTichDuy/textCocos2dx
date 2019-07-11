#include "PauseScene.h"
#include "ui/CocosGUI.h"
#include"SettingScene.h"


static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

cocos2d::Scene * PauseScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PauseScene::create();
	scene->addChild(layer, -10);

	return scene;
}

bool PauseScene::init()
{
	if (!Layer::init())
	{
		return false;

	}
	screenSize = Director::getInstance()->getVisibleSize();

	// add menu sprite
	auto menuPause = Sprite::create("Pause/Window.png");

	if (menuPause == nullptr)
	{
		problemLoading("'Pause/Window.png'");
	}
	else
	{
		menuPause->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
		menuPause->setScale(screenSize.width / 3 / menuPause->getContentSize().width,
			screenSize.height * 2 / 3 / menuPause->getContentSize().height);
		this->addChild(menuPause, 0);
	}
	// add text pause
	auto textPause = Sprite::create("Pause/Header.png");

	if (textPause == nullptr)
	{
		problemLoading("'Pause/Header.png'");
	}
	else
	{
		textPause->setPosition(screenSize.width / 2, screenSize.height / 1.5);
		textPause->setScale(screenSize.width / 10 / textPause->getContentSize().width);
		this->addChild(textPause, 1);
	}
	// add button resume
	auto buttonResume = ui::Button::create("Buttons/BTNs/Play_BTN.png");
	if (buttonResume == nullptr)
	{
		problemLoading("'Buttons/BTNs/Play_BTN.png'");
	}
	else
	{
		buttonResume->setPosition(Vec2(screenSize.width / 2,
			screenSize.height / 2 - buttonResume->getContentSize().height/4));
		buttonResume->setScale(textPause->getScale());

		buttonResume->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				this->buttonPauseCallback(sender);
				break;
			default:
				break;
			}
		});

		this->addChild(buttonResume, 2);
	}


	// add button Settings_BTN

	auto buttonSetting = ui::Button::create("Buttons/BTNs/Settings_BTN.png");

	if (buttonSetting == nullptr)
	{
		problemLoading("'Buttons/BTNs/Settings_BTN.png'");
	}
	else
	{
		buttonSetting->setPosition(Vec2(screenSize.width / 2 + buttonSetting->getContentSize().width / 2,
			screenSize.height / 2 - buttonSetting->getContentSize().height/4));
		buttonSetting->setScale(textPause->getScale());

		buttonSetting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				this->buttonSettingCallback(sender);
				break;
			default:
				break;
			}
		});

		this->addChild(buttonSetting, 2);
	}
	// add button replay

	auto buttonReplay = ui::Button::create("Buttons/BTNs/Replay_BTN.png");

	if (buttonReplay == nullptr)
	{
		problemLoading("'Buttons/BTNs/Replay_BTN.png'");
	}
	else
	{
		buttonReplay->setPosition(Vec2(screenSize.width / 2 - buttonReplay->getContentSize().width / 2,
			screenSize.height / 2 - buttonReplay->getContentSize().height / 4));
		buttonReplay->setScale(textPause->getScale());
		this->addChild(buttonReplay, 2);
	}


	return true;
}

void PauseScene::buttonPauseCallback(cocos2d::Ref * sender)
{
	Director::getInstance()->popScene();
}
void PauseScene::buttonSettingCallback(Ref *sender)
{
	Director::getInstance()->pushScene(SettingScene::createScene());
}
