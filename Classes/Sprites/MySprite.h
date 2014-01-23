//
//  MySprite.h
//  MyGame
//
//  Created by ludawei on 14-1-23.
//
//

#ifndef __MyGame__MySprite__
#define __MyGame__MySprite__

#include "cocos2d.h"
USING_NS_CC;

class MySprite : public Sprite
{
public:
    MySprite();
    ~MySprite();
    static MySprite* create(Texture2D *texture);
    
    void setIndex(int index);
    int getIndex();
    
private:
    void initData();
    int index;
};

#endif /* defined(__MyGame__MySprite__) */
