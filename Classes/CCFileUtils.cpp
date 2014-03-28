
#include "CCFileUtils.h"  

string TDInvFileUtils::getFileByName(string pFileName){  
	//��һ�Ȼ�ȡ�ļ���·��  
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + pFileName;  
	CCLOG("path = %s",path.c_str());  

	//����һ���ļ�ָ��  
	FILE* file = fopen(path.c_str(), "r");  

	if (file) {
		char* buf;  //Ҫ��ȡ���ַ���  
		int len;    //��ȡ�ĳ���  
		/*��ȡ����*/  
		fseek(file, 0, SEEK_END);   //�Ƶ�β��  
		len = ftell(file);          //��ȡ����  
		rewind(file);               //�ع�ԭλ  
		CCLOG("count the file content len = %d",len);  
		//����buf�ռ�  
		buf = (char*)malloc(sizeof(char) * len + 1);  
		if (!buf) {  
			CCLOG("malloc space is not enough.");  
			return NULL;  
		}  

		//��ȡ�ļ�  
		//��ȡ����buf����λ��С�����ȣ��ļ�ָ��  
		int rLen = fread(buf, sizeof(char), len, file);  
		buf[rLen] = '\0';  
		CCLOG("has read Length = %d",rLen);  
		CCLOG("has read content = %s",buf);  

		string result = buf;  
		fclose(file);  
		free(buf);  
		return result;  
	}  
	else 
	{
		CCLOG("open file error.");  
	}

	return "";  
}  

bool TDInvFileUtils::saveFile(char *pContent, string pFileName){  
	//��һ��ȡ������ļ�·��  
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + pFileName;  
	CCLOG("wanna save file path = %s",path.c_str());  

	//����һ���ļ�ָ��  
	//·����ģʽ  
	FILE* file = fopen(path.c_str(), "w");  
	if (file) {  
		fputs(pContent, file);  
		fclose(file);  
	}  
	else  
		CCLOG("save file error.");  

	return false;  
}  