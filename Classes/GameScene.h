//
//  GameScene.h
//  MyGame
//
//  Created by ludawei on 14-1-17.
//
//

#ifndef __MyGame__GameScene__
#define __MyGame__GameScene__

#include "cocos2d.h"
#include "MySnake.h"

USING_NS_CC;

static const int col_num = 16;
static const int row_num = 20;

class GameScene : public cocos2d::Layer
{
private:
    MySnake* snake;
    Size visibleSize;
    Point beginTouchPoint;
    long lastClickTime;
    
    void menuCallback(Object* pSender);
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    static GameScene* sharedGameScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    //重写触屏相关函数----
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    SpriteBatchNode* bgItemBatch;
    Point getBgItemPozitionByTag(int tag);
    
    void resetGame();
};

#endif /* defined(__MyGame__GameScene__) */
