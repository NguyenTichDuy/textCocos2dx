/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"	
#include "StartScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// add background

	auto background = Sprite::create("BackgroundFirst.png");

	if (background == nullptr)
	{
		problemLoading("'BackgroundFirst.png'");
	}
	else
	{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
		this->addChild(background, -10);
	}
	// add space ship
	auto spaceShip = Sprite::create("spaceship1.png");

	if (spaceShip == nullptr)
	{
		problemLoading("'spaceship1.png'");
	}
	else
	{
		spaceShip->setPosition(Vec2(visibleSize.width / 10, visibleSize.height / 2));
		spaceShip->setRotation(90);
		spaceShip->setScale(0.5);
		this->addChild(spaceShip, 1);
	}
	// add space ship action
	auto actionSpace = MoveTo::create(4, Vec2(visibleSize.width, visibleSize.height / 2));
	auto rotationDown = RotateBy::create(0.5, 45);
	auto rotationUp = RotateBy::create(0.5,(-45));
	
	spaceShip->runAction(actionSpace);


	// add logo gameloft
	auto logoGl = Sprite::create("LogoGL.png");

	if (logoGl == nullptr)
	{
		problemLoading("'LogoGL.png");
	}
	else
	{
		logoGl->setAnchorPoint(Vec2(0, 0));
		logoGl->setScale(0.05);
		logoGl->setPosition(visibleSize.width - logoGl->getContentSize().width/20, 0);
		
		this->addChild(logoGl, 1);
	}



	// 3. add your codes below...


	// add loading text
	auto loadingText = Label::create("Loading...", "fonts/Marker Felt.ttf", 32);

	if (loadingText == nullptr)
	{
		problemLoading("fonts/Marker Felt.ttf");
	}
	else
	{
		loadingText->setPosition(Vec2(visibleSize.width / 2 
			+ origin.x, visibleSize.height / 3.9 + loadingText->getContentSize().height + origin.y));
		loadingText->enableGlow(Color4B::BLACK);
		
		loadingText->setColor(Color3B::GRAY);
		this->addChild(loadingText, 0);
	}
	// add loading bar bg
	auto loadingBarBg = Sprite::create("loadingbar_bg.png");
	if (loadingBarBg == nullptr)
	{
		problemLoading("'loadingbar_bg.png'");
	}
	else
	{
		loadingBarBg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));
		loadingBarBg->setScaleX(2);
		this->addChild(loadingBarBg, -1);
	}
	// add loading bar

	auto loadingBar = ui::LoadingBar::create("loadingbar.png");

	if (loadingBar == nullptr)
	{
		problemLoading("'loadingbar.png'");
	}
	else
	{
		loadingBar->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));
		loadingBar->setScaleX(2);
		loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);

		loadingBar->setPercent(0);

		this->addChild(loadingBar, 0);

		this->schedule([=](float delta) {
			float percent = loadingBar->getPercent();
			percent++;
			loadingBar->setPercent(percent);
			if (percent >= 100.0f)
			{
				this->unschedule("updateLoadingBar");
			}
		}, 0.02f, "updateLoadingBar");
	}

	auto gotoNext = CallFunc::create([]()
	{
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, StartScene::createSecene(), Color3B(0,255,255)));
	});
	auto sequence = Sequence::create(DelayTime::create(3), gotoNext, nullptr);
	runAction(sequence);
	

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
