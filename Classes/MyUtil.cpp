//
//  MyUtil.cpp
//  MyGame
//
//  Created by ludawei on 14-1-22.
//
//

#include "MyUtil.h"
MyUtil::MyUtil()
{
    
}

MyUtil::~MyUtil()
{
    
}

String* MyUtil::pointToString(cocos2d::Point p)
{
    return String::createWithFormat("%d-%d", (int)p.x, (int)p.y);
}

Point MyUtil::StringToPoint(cocos2d::String *str)
{
    Array* pArray = str->componentsSeparatedByString("-");
    String* xString = (String *)pArray->getObjectAtIndex(0);
    String* yString = (String *)pArray->getLastObject();
    return Point(xString->floatValue(), yString->floatValue());
}

long MyUtil::getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}