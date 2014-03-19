//
//  NumberSprite.cpp
//  ShowNumberNodeTest
//
//  Created by Za aa on 13-7-14.
//
//

#include "NumberSprite.h"

bool NumberSprite::myInit(float width, float lenght)
{
    s_width     =   width;
    s_lenght    =   lenght;


}
NumberSprite *NumberSprite::CreateNumberSprite(CCTexture2D *pTexture, float width, float lenght)
{
    NumberSprite *pobSprite = new NumberSprite();

    if (pobSprite && pobSprite->initWithTexture(pTexture)  )
    {
        pobSprite->setVisible(false);
        pobSprite->myInit(width , lenght);
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void NumberSprite::f_ShowNumber(int num)
{
   
    this->setVisible(true)  ;
    this->setTextureRect(CCRectMake(s_width * num, 0, s_width, s_lenght));
}
