//
//  MySnake.cpp
//  MyGame
//
//  Created by ludawei on 14-1-17.
//
//

#include "MySnake.h"
#include "cocos-ext.h"
#include "MyUtil.h"
#include "GameScene.h"
#include "GameOverScene.h"

static int batchNodeStartTag = 200;

MySnake::MySnake()
{
    
}

MySnake::~MySnake()
{
    
}

MySnake* MySnake::create(const char* pngName)
{
    auto snakeSpriteBatchNode = new MySnake();
    if (snakeSpriteBatchNode && snakeSpriteBatchNode->initWithFile(pngName, 1000))
	{
		snakeSpriteBatchNode->initData();
		snakeSpriteBatchNode->autorelease();
		return snakeSpriteBatchNode;
	}
	CC_SAFE_DELETE(snakeSpriteBatchNode);
    return NULL;
}

#pragma mark - initData
void MySnake::initData()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    
    for (int i=0; i < 4; i++) {
        MySprite *sprite = MySprite::create(this->getTexture());
        sprite->setAnchorPoint(Point(0, 1));
        sprite->setTag(i+batchNodeStartTag);
//        sprite->setPosition( GameScene::sharedGameScene()->getBgItemPozitionByTag(3-i) );
        sprite->setIndex(3-i);
        this->addChild(sprite);
    }
    
    snakeHeader = (MySprite *)this->getChildByTag(batchNodeStartTag);
    type = moveTypeRight;
    
    randomSprite = MySprite::create(this->getTexture());
    randomSprite->setAnchorPoint(Point(0, 1));
    this->addChild(randomSprite);
    changeRandomSpritePozition();
    
    unschedule(schedule_selector(MySnake::moveSnake));
    schedule(schedule_selector(MySnake::moveSnake), 0.5f);
    
    isNormal = true;
}

void MySnake::addSnake(int index)
{
    MySprite *sprite = MySprite::create(this->getTexture());
    sprite->setAnchorPoint(Point(0, 1));
    sprite->setTag(getChildrenCount()-1+batchNodeStartTag);
    sprite->setIndex(index);
    this->addChild(sprite);
}

void MySnake::moveSnake(float dt)
{
    MySprite *footSnake = (MySprite *)getChildByTag(getChildrenCount()-2+batchNodeStartTag);
    for (int i=getChildrenCount()-2; i >= 0; i--) {
        MySprite *sprite = (MySprite *)getChildByTag(i+batchNodeStartTag);
        MySprite *sprite1 = (MySprite *)getChildByTag(i-1+batchNodeStartTag);
        if (sprite != snakeHeader) {
            sprite->setIndex(sprite1->getIndex()); //setPosition(getChildByTag(i-1+batchNodeStartTag)->getPosition());
        }
        else
        {
            this->moveSnakeHeader();
        }
    }
    
    if (snakeHeader->getIndex() == randomSprite->getIndex()) {
        
        addSnake(footSnake->getIndex());
        changeRandomSpritePozition();
    }
    
    checkGameOver();
    
    isNormal = true;
}

void MySnake::moveSnakeHeader()
{
    int row, col, newIndex;
    row = snakeHeader->getIndex()/col_num;
    col = snakeHeader->getIndex()%col_num;
    switch (type) {
        case moveTypeUp:
        {
            newIndex = snakeHeader->getIndex() - col_num;
            if (newIndex < 0) {
                newIndex = (row_num-1)*col_num + col;
            }
            break;
        }
        case moveTypeDown:
        {
            newIndex = snakeHeader->getIndex() + col_num;
            if (newIndex > row_num*col_num) {
                newIndex = col;
            }
            break;
        }
        case moveTypeLeft:
        {
            newIndex = snakeHeader->getIndex() - 1;
            if (newIndex < row*col_num) {
                newIndex = (row+1)*col_num - 1;
            }
            break;
        }
        case moveTypeRight:
        {
            newIndex = snakeHeader->getIndex() + 1;
            if (newIndex >= (row+1)*col_num) {
                newIndex = row*col_num;
            }
            break;
        }
        default:
            break;
    }
    snakeHeader->setIndex(newIndex);
}

void MySnake::changeType(SnakeMoveType type)
{
    if ((this->type <= moveTypeDown && type > moveTypeDown) || (this->type > moveTypeDown && type <= moveTypeDown)) {
        this->type = type;
    }
}

void MySnake::changeRandomSpritePozition()
{
    Array *totalArray = Array::createWithCapacity(col_num * row_num);
    for (int i=0; i<totalArray->capacity(); i++) {
        totalArray->addObject(Integer::create(i));
    }
    
    for (int i=0; i < getChildrenCount()-1; i++) {
        MySprite *sprite = (MySprite *)getChildByTag(i+batchNodeStartTag);
        
        totalArray->removeObjectAtIndex(sprite->getIndex());
    }
    
    int randIndex = (CCRANDOM_0_1()+1) * totalArray->count();
    randIndex = CCRANDOM_0_1() * totalArray->count();
    Integer* pozitionIndex = (Integer *)totalArray->getObjectAtIndex(randIndex);
 
    randomSprite->setIndex(pozitionIndex->getValue());
}

void MySnake::checkGameOver()
{
    for (int i=1; i < getChildrenCount()-1; i++) {
        MySprite *sprite = (MySprite *)getChildByTag(i+batchNodeStartTag);
        
        if (sprite->getIndex() == snakeHeader->getIndex()) {
            auto scene = GameOverScene::createScene();
            Director::getInstance()->pushScene(scene);
        }
    }
}


