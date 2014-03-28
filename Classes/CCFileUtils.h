
  
#ifndef __CCFILEUTILS_H_  
#define __CCFILEUTILS_H_  
  
#include <iostream>  
#include "cocos2d.h"  
using namespace cocos2d;  
using namespace std;  
  
/** 负责操作文件储存和读取 
 */  
  
class TDInvFileUtils {  
public:  
    /** 读取本地文件，返回数据 */  
    static string getFileByName(string pFileName);  
      
    /** 储存内容到文件 */  
    static bool saveFile(char* pContent,string pFileName);  
      
};  


#endif /*__CCFILEUTILS_H_*/