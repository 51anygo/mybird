
  
#ifndef __CCFILEUTILS_H_  
#define __CCFILEUTILS_H_  
  
#include <iostream>  
#include "cocos2d.h"  
using namespace cocos2d;  
using namespace std;  
  
/** ��������ļ�����Ͷ�ȡ 
 */  
  
class TDInvFileUtils {  
public:  
    /** ��ȡ�����ļ����������� */  
    static string getFileByName(string pFileName);  
      
    /** �������ݵ��ļ� */  
    static bool saveFile(char* pContent,string pFileName);  
      
};  


#endif /*__CCFILEUTILS_H_*/