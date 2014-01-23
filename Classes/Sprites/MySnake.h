//
//  MySnake.h
//  MyGame
//
//  Created by ludawei on 14-1-17.
//
//

#ifndef __MyGame__MySnake__
#define __MyGame__MySnake__

#include "cocos2d.h"
#include "MySprite.h"
USING_NS_CC;

enum SnakeMoveType{
    moveTypeUp,
    moveTypeDown,
    moveTypeLeft,
    moveTypeRight
};

class MySnake : public SpriteBatchNode
{
public:
    MySnake();
    ~MySnake();
    static MySnake* create(const char* pngName);
    void changeType(SnakeMoveType type);
    void changeRandomSpritePozition();
    
private:
    Size visibleSize;
    
    void initData();
    MySprite *snakeHeader, *randomSprite;
    SnakeMoveType type;
    
    void moveSnake(float dt);
    void modifyPozition(Node *node);
    void moveSnakeHeader();
};

#endif /* defined(__MyGame__MySnake__) */
