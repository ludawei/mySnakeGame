//
//  GameOverScene.cpp
//  MyGame
//
//  Created by ludawei on 14-1-28.
//
//

#include "GameOverScene.h"
#include "GameScene.h"
GameOverScene::GameOverScene()
{
    
}

GameOverScene::~GameOverScene()
{
    
}

Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameOverScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    initData();
    return true;
}

#pragma mark - initData
void GameOverScene::initData()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // add your codes here...
    // 开始按钮
    auto startLabel = LabelTTF::create("Start agine", "Arial", 50);
    auto startItem = MenuItemLabel::create(startLabel, CC_CALLBACK_1(GameOverScene::menuCallback, this));
	startItem->setPosition(visibleSize.width/2, visibleSize.height/2);
    startItem->setTag(10);
    
    // 退出按钮
    auto returnLabel = LabelTTF::create("return to main", "Arial", 50);
    auto returnItem = MenuItemLabel::create(returnLabel, CC_CALLBACK_1(GameOverScene::menuCallback, this));
	returnItem->setPosition(startItem->getPositionX(), startItem->getPositionY() - returnItem->getContentSize().height);
    returnItem->setTag(11);
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, returnItem, NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
}

void GameOverScene::menuCallback(Object* pSender)
{
    auto item = (LabelTTF *)pSender;
    if (item->getTag() == 10) {
        GameScene::sharedGameScene()->resetGame();
        Director::getInstance()->popScene();
    }
    else if (item->getTag() == 11)
    {
        Director::getInstance()->popToRootScene();
    }
}
