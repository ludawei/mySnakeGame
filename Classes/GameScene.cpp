//
//  GameScene.cpp
//  MyGame
//
//  Created by ludawei on 14-1-17.
//
//

#include "GameScene.h"
#include "MyUtil.h"

USING_NS_CC;

#define MENU_ITEM_TAG 300

static GameScene* mySharedGameScene = NULL;
GameScene* GameScene::sharedGameScene()
{
    return mySharedGameScene;
}

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    log("GameScene init!");
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    mySharedGameScene = this;
    
    visibleSize = Director::getInstance()->getVisibleSize();
//    Point origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    
    // 按钮
    auto leftLabel = LabelTTF::create("Left", "Arial", 50);
    auto leftItem = MenuItemLabel::create(leftLabel, CC_CALLBACK_1(GameScene::menuCallback, this));
    leftItem->setTag(moveTypeLeft+MENU_ITEM_TAG);
	leftItem->setPosition(320, 150);
    
    auto rightLabel = LabelTTF::create("Right", "Arial", 50);
    auto rightItem = MenuItemLabel::create(rightLabel, CC_CALLBACK_1(GameScene::menuCallback, this));
    rightItem->setTag(moveTypeRight+MENU_ITEM_TAG);
	rightItem->setPosition(580, 150);
    
    auto upLabel = LabelTTF::create("Up", "Arial", 50);
    auto upItem = MenuItemLabel::create(upLabel, CC_CALLBACK_1(GameScene::menuCallback, this));
    upItem->setTag(moveTypeUp+MENU_ITEM_TAG);
	upItem->setPosition(450, 230);
    
    auto downLabel = LabelTTF::create("Down", "Arial", 50);
    auto downItem = MenuItemLabel::create(downLabel, CC_CALLBACK_1(GameScene::menuCallback, this));
    downItem->setTag(moveTypeDown+MENU_ITEM_TAG);
	downItem->setPosition(450, 70);
    
    auto stopStartLabel = LabelTTF::create("stop", "Arial", 50);
    auto stopStartItem = MenuItemLabel::create(stopStartLabel, CC_CALLBACK_1(GameScene::menuCallback, this));
    stopStartItem->setTag(10+MENU_ITEM_TAG);
	stopStartItem->setPosition(80, 250);
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(leftItem, rightItem, upItem, downItem, stopStartItem, NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 10);
    
    /////////////////////////////
    // 3. add your codes below...
    
    bgItemBatch = SpriteBatchNode::create("bg_item.png");
//    bg_item->setPosition(Point::ZERO);
    this->addChild(bgItemBatch);
    
    for (int j = 0; j < row_num; j++) {
        for (int i = 0; i < col_num; i++) {
            auto sprite = Sprite::createWithTexture(bgItemBatch->getTexture());
            sprite->setAnchorPoint(Point(0, 1));
            sprite->setTag(col_num*j+i);
            sprite->setPosition(Point(sprite->getContentSize().width*i, visibleSize.height - sprite->getContentSize().height*j));
            bgItemBatch->addChild(sprite);
        }
    }
    
    snake = MySnake::create("Icon-40.png");
    this->addChild(snake, 2);
    
    return true;
}

void GameScene::onEnter()
{
	log("onEnter mainScene");
    
	CCLayer::onEnter();
    
    // Register Touch Event
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
//    snake->runAction(MoveTo::create(10, Point(visibleSize.width, 0)));
}

void GameScene::onExit()
{
    CCLayer::onExit();
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log("%s","mainScene~ccTouchBegan");
//    snake->setPosition(touch->getLocation());
    beginTouchPoint = touch->getLocationInView();
    
    return true;
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
//    snake->setPosition(touch->getLocation());
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	log("%s","mainScene~~~ccTouchEnded");
}

void GameScene::menuCallback(Object* pSender)
{
    auto item = (MenuItemLabel *)pSender;
    if (item->getTag() == 10 + MENU_ITEM_TAG) {
        
        auto stopStartLabel = (LabelTTF *)item->getLabel();
        if (strcmp(stopStartLabel->getString().c_str(), "stop") == 0) {
            stopStartLabel->setString("start");
            Director::getInstance()->pause();
        }
        else
        {
            stopStartLabel->setString("stop");
            Director::getInstance()->resume();
        }
        return;
    }
    
    if (!snake->isNormal) {
        return;
    }
    SnakeMoveType type =(SnakeMoveType)(item->getTag()-MENU_ITEM_TAG);
    snake->changeType(type);
    
    snake->isNormal = false;
}

Point GameScene::getBgItemPozitionByTag(int tag)
{
    return bgItemBatch->getChildByTag(tag)->getPosition();
}

void GameScene::resetGame()
{
//    snake = NULL;
    snake->removeFromParentAndCleanup(true);
    snake = MySnake::create("Icon-40.png");
    this->addChild(snake, 2);
}