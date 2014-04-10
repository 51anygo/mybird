//
//  ShowNumberNode.h
//  ShowNumberNodeTest
//
//  Created by Za aa on 13-7-12.
//
//

#ifndef __ShowNumberNodeTest__ShowNumberNode__
#define __ShowNumberNodeTest__ShowNumberNode__

#include "cocos2d.h"
USING_NS_CC;
/*

*/

#define SCROLLTIME 0.2f
class ShowNumberNode : public CCNode
{
public:
    /*
        ����һ��showNumberNode�ڵ�
    ������
        path: �ļ���
        numberMAX��������ʾ�����ֵ
        showwidth: ÿ������ͼƬ�Ŀ��
        showheight:ÿ������ͼƬ�Ŀ��

    */
    static ShowNumberNode *CreateShowNumberNode(const char *path, int numberMAX, float showwidth, float showheight);

    /*ͬ��*/
    bool Init(const char *path, int numberMAX, float showwidth, float showheight);

    
    // �޸���ʾ����,ֱ����ʾ�����޹���
    void f_ShowNumber(int number);
    


private: 
    //������־��鵽�ڵ�,����������
    void f_addSprite();

    //�ж��������ֵ�λ�������磺11����2λ��333����3λ
    int f_NumberLength(int number);

    //����num���ұ߿�ʼ��kλ���ֵ�ֵ,���磺654321,��3����3��Ҳ���ǰ�λ�ϵ�����
    int f_GetNumber(int num, int k);

private:
   
    //���ڱ����������ֵ
    int s_NumberMax;

    //�����������λ��
    int s_NumberLength;

    //ͼƬ���
    float s_ShowWidth;

    //    ͼƬ�ĸ߶�
    float s_ShowHeight;

    CCSpriteBatchNode *batchNode ;





};


#endif /* defined(__ShowNumberNodeTest__ShowNumberNode__) */
