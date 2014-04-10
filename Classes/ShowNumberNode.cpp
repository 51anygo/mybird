//
//  ShowNumberNode.cpp
//  ShowNumberNodeTest
//
//  Created by Za aa on 13-7-12.
//
//

#include "ShowNumberNode.h"
#include "NumberSprite.h"
ShowNumberNode *ShowNumberNode::CreateShowNumberNode(const char *path, int numberMAX, float showwidth, float showheight)
{
    ShowNumberNode *pobSprite = new ShowNumberNode();

    if (pobSprite )
    {

        pobSprite->Init(path , numberMAX, showwidth, showheight);
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;

}
bool ShowNumberNode::Init(const char *path, int numberMAX, float showwidth, float showheight)
{
    //初始化参数
    this->s_NumberMax = numberMAX;
    this->s_ShowWidth = showwidth;
    this->s_ShowHeight = showheight;

    //计算数字长度
    s_NumberLength = f_NumberLength(numberMAX);

    //
    batchNode = CCSpriteBatchNode::create(path);

    //将numbersprite 添加进节点
    f_addSprite();

    return true;

}
/*添加数字精灵到节点,并进行排列*/
void ShowNumberNode::f_addSprite()
{

    for (int i = 0; i < s_NumberLength; i++)
    {
        /* code */
        NumberSprite *nsp  = NumberSprite::CreateNumberSprite(batchNode->getTexture(), s_ShowWidth, s_ShowHeight);

        nsp->setPosition(ccp(-s_ShowWidth * i, 0));

        batchNode->addChild(nsp, 0, i);

    }

    this->addChild(batchNode);
}

// 修改显示数字
void ShowNumberNode::f_ShowNumber(int number)
{
    // s_NumberMax=number;
    if (number < 0 || number > s_NumberMax)
        return;

    int numlength = f_NumberLength(number);


    for (int i = 0; i < s_NumberLength; i++)
    {
        /* code */
        int num = f_GetNumber(number, i + 1);


        NumberSprite *nsp =  (NumberSprite * ) batchNode->getChildByTag(i);

        //将超出数字的隐藏，比如：最大值是999，现在需要显示33，那就是隐藏百位上的0
        if (i >= numlength)
        {
            //TODO :
            nsp->setVisible(false);
           //break;
        }
        else
        {
            nsp->setVisible(true);
            nsp->f_ShowNumber(num);
        }

       

    }
    
}





//判断输入数字的位数，比如：11就是2位，333就是3位
int ShowNumberNode::f_NumberLength(int number)
{
    if(number == 0 )
        return  1;
    int flag = 0;
    while (number)
    {
        number /= 10;
        flag++;
    }
    return flag;

}

//返回num从右边开始第k位数字的值
int ShowNumberNode::f_GetNumber(int num, int k)
{
    while (k > 1) //我们计数是从1开始的，电脑是从0开始的。当k=1时，依然大于0，还要执行一次循环，那样就多减了一位，所以到1就结束

    {
        num = num / 10;
        k--;

    }
    return num % 10 ; //返回数位的值
}