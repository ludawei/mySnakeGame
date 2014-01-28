//
//  GameOverScene.h
//  MyGame
//
//  Created by ludawei on 14-1-28.
//
//

#ifndef __MyGame__GameOverScene__
#define __MyGame__GameOverScene__

#include "cocos2d.h"
USING_NS_CC;

class GameOverScene : public Layer
{
public:
    GameOverScene();
    ~GameOverScene();
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameOverScene);
    
private:
    void initData();
    
    void menuCallback(Object* pSender);
};

#endif /* defined(__MyGame__GameOverScene__) */
