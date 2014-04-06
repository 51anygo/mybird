/*
 The MIT License (MIT)
 
 Copyright (c) 2013 SuXinDe (Email: suxinde2009@126.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */



#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "B2Sprite.h"
#include "CCShake.h"
#include "ShowNumberNode.h"
#include "CCFileUtils.h"

#define RATIO 32.0f // 比例 48
#define SPRITE_TAG_BAR 0x01
#define SPRITE_TAG_SCORE 0x02
#define SPRITE_TAG_GROUND 0x03
#define SPRITE_TAG_BIRD   0x04
#define SPRITE_TAG_CHAR   0x06
#define SPRITE_TAG_OVER   0x07
#define GGROUNDNUM 5
#define GBACKGROUNDNUM 3
#define MOVESPEED 2
#define gDownVelocity -35
#define gUpVelocity 10
#define gAddBarTime 1.5

#define gBirdX  1/2
#define gBirdY  1/2

enum RUNSTAT{
	GOSTART,
	GETREADY,
	RUNNING,
	GAMEOVER
};

typedef struct VECPOINT{
   
    float x;
    float y;
}VPOINT;

class HelloWorld: public cocos2d::CCLayer,
public b2ContactListener
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void openUmengShare(CCObject * pSender);
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

    ////////////////////////////////////////////////////
    // 下面添加自己的代码
    ////////////////////////////////////////////////////
	CCSize mgroundSize;
    int myflag;
	int myangle;
	int testnum;
	int iFlyKeep;
	float gameoverX;
	float gameoverY;
	float scoreX;
	float scoreY;
	float startX;
	float startY;
	float topX;
	float topY;
	int myscore;
	bool m_bhitbar;
	bool m_bnew;
	//float		m_addbartime;
	list<CCSprite *> m_pDownBarVec;
    b2World     *mWorld;                // box2D world
    B2Sprite    *mBird;                 // bird的sprite
    CCSize      mScreenSize;           // 屏幕尺寸
	float       mFPS;
	float       mfac;
	float		mfax;
    CCSprite    *mBarContainer;         //
	vector<B2Sprite*> m_pGroundVec;
    CCSprite    *m_pBackGround[GBACKGROUNDNUM];
	CCSprite    *m_pScore,*m_pRate,*m_pStart,*m_pTop,*m_pFlappyBird,*m_pGameOver,*m_pShare;
	CCSprite    *m_pHand,*m_pUp,*m_pLeftTap,*m_pRightTap,*m_pReady,*m_pGBird;
	int			m_bestscore;
	int          m_igroundnum;
	int          m_ilastground;
	RUNSTAT      m_istatus; //0准备 1开始 2结束
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void BeginContact(b2Contact* contact);
    virtual void update(float dt);

    void ScoreSchedule(float dt);
private:
	ShowNumberNode * msnn;
	void initAction();
	void logic(float dt);
	void addNew();
	void addNumberNode();
	//void addScoreNum(int num);
	void MoveScore(float dt);
	void MoveStart(float dt);
	void MoveTop(float dt);
	void MoveScoreAdd(float dt);
	void MoveGameOver(float dt);
    void addBird();
	void addScore();
	void addGameOver();
	void addRate();
	void addShare(float dt);
	void addStart();
	void addFlappyBird();
	void addTop();
	void addHand();
	void addReady();
	void addUp();
	void addLeftTap();
	void addRightTap();
	void addGBird();
	void goReady();
    int addGround(int index);
	void addBackGround(int index);
    void initWorld();
    void addBar(float dt);
    void addBarContainer();
    void startGame(float dt);
    void stopGame();
	void addGold();
	void addSilver();
	void addBestScore();
	
    
};

#endif // __HELLOWORLD_SCENE_H__
