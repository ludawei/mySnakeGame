//
//  MyUtil.h
//  MyGame
//
//  Created by ludawei on 14-1-22.
//
//

#ifndef __MyGame__MyUtil__
#define __MyGame__MyUtil__

#include "cocos2d.h"
USING_NS_CC;

class MyUtil : public Object
{
public:
    MyUtil();
    ~MyUtil();
    static String* pointToString(Point p);
    static Point StringToPoint(String* str);
    
    static long getCurrentTime();
};

#endif /* defined(__MyGame__MyUtil__) */
