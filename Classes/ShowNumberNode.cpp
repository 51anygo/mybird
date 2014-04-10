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
    //��ʼ������
    this->s_NumberMax = numberMAX;
    this->s_ShowWidth = showwidth;
    this->s_ShowHeight = showheight;

    //�������ֳ���
    s_NumberLength = f_NumberLength(numberMAX);

    //
    batchNode = CCSpriteBatchNode::create(path);

    //��numbersprite ��ӽ��ڵ�
    f_addSprite();

    return true;

}
/*������־��鵽�ڵ�,����������*/
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

// �޸���ʾ����
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

        //���������ֵ����أ����磺���ֵ��999��������Ҫ��ʾ33���Ǿ������ذ�λ�ϵ�0
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





//�ж��������ֵ�λ�������磺11����2λ��333����3λ
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

//����num���ұ߿�ʼ��kλ���ֵ�ֵ
int ShowNumberNode::f_GetNumber(int num, int k)
{
    while (k > 1) //���Ǽ����Ǵ�1��ʼ�ģ������Ǵ�0��ʼ�ġ���k=1ʱ����Ȼ����0����Ҫִ��һ��ѭ���������Ͷ����һλ�����Ե�1�ͽ���

    {
        num = num / 10;
        k--;

    }
    return num % 10 ; //������λ��ֵ
}