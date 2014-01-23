//
//  MySprite.cpp
//  MyGame
//
//  Created by ludawei on 14-1-23.
//
//

#include "MySprite.h"
#include "GameScene.h"

MySprite::MySprite()
{
    
}

MySprite::~MySprite()
{
    
}

MySprite* MySprite::create(Texture2D *texture)
{
    auto sprite = new MySprite();
    if (sprite && sprite->initWithTexture(texture))
	{
		sprite->initData();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
    return NULL;
}

#pragma mark - initData
void MySprite::initData()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // add your codes here...
    
}

void MySprite::setIndex(int index)
{
    this->index = index;
    this->setPosition( GameScene::sharedGameScene()->getBgItemPozitionByTag(index) );
}

int MySprite::getIndex()
{
    return index;
}
