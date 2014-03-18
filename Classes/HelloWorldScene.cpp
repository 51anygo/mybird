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

#include "HelloWorldScene.h"

#include "SGPlayMusic.h"
USING_NS_CC;
//clone Flappy Bird
//http://comandobueiro.com.br/flappy-bird-clone-com-appcelerator-e-lanica.html
//http://lanica.co/flappy-clone/

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    //播放背景音乐
   // CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_JUMP, true);
    ////////////////////////////////////////////////////
    // 下面添加创建自己的Sprite的代码
    ////////////////////////////////////////////////////
    
    mScreenSize = CCDirector::sharedDirector()->getVisibleSize();
    initWorld();
	addBackGround();
	addGround1();
	addGround2();
    addBird();
    addBarContainer();
    setTouchEnabled(true);
    myflag=0;
    scheduleOnce(schedule_selector(HelloWorld::startGame), 1);
	//创建动画
	initAction();
    return true;
}

void HelloWorld::startGame(float dt){
    scheduleUpdate();
    schedule(schedule_selector(HelloWorld::addBar), 3);
}

void HelloWorld::stopGame(){
    unscheduleUpdate();
    unschedule(schedule_selector(HelloWorld::addBar));
}

void HelloWorld::initWorld(){
    mWorld = new b2World(b2Vec2(0, -20));
    mWorld->SetContactListener(this);
}


void HelloWorld::initAction()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bird.plist");
    CCArray *animFrames = CCArray::create();
    for (int i = 1; i < 4; i++)
    {
        CCString *name = CCString::createWithFormat("bird%d.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
		if(i == 1)
		{
			CCSprite *pSprite = CCSprite::createWithSpriteFrame(frame);
			this->addChild(pSprite);
		}
        animFrames->addObject(frame);
    }    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
	CCAnimate* pAnimate = CCAnimate::create(animation);
	CCActionInterval* seq = (CCActionInterval *)(CCSequence::create(pAnimate, NULL));    // 创建顺序执行action
	mBird->runAction(CCRepeatForever::create(seq));
	/*

	CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames(pAniFrame, 0.05f);    // 0.05f是指经过50毫秒就要切换下一张png图
	CCAnimate* pAnimate = CCAnimate::create(pAnimation);
	CCActionInterval* seq = (CCActionInterval *)(CCSequence::create(pAnimate, NULL));    // 创建顺序执行action
	pSprite->runAction(CCRepeatForever::create(seq));*/
}

void HelloWorld::addBird(){
    mBird = B2Sprite::create("bird.png");
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    // 单位为 米
    bodyDef.position = b2Vec2(mScreenSize.width/2.0f/RATIO, 9); // 10m以内模拟效果较高效。
    b2Body *birdBody = mWorld->CreateBody(&bodyDef);
    
    // 碰撞
    CCSize birdSize = mBird->getContentSize();
    b2PolygonShape birdShape;
    birdShape.SetAsBox(birdSize.width/2.0f/RATIO, birdSize.height/2.0f/RATIO); // 半宽，半高
    b2FixtureDef birdFixtureDef;
    birdFixtureDef.shape = &birdShape;
    
    birdBody->CreateFixture(&birdFixtureDef);
    
    mBird->setPTMRatio(RATIO);
    mBird->setB2Body(birdBody);
    addChild(mBird,4);
	
}


void HelloWorld::addGround1() {
    m_pGround1 = B2Sprite::create("ground.png");
    CCSize groundSize = m_pGround1->getContentSize();
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = b2Vec2(groundSize.width/2.0f/RATIO,
                              groundSize.height/2.0f/RATIO);
    b2Body *groundBody = mWorld->CreateBody(&bodyDef);

    b2PolygonShape groundShape;
    groundShape.SetAsBox(groundSize.width/2.0f/RATIO, groundSize.height/2.0f/RATIO);
    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &groundShape;
    groundBody->CreateFixture(&groundFixtureDef);
    
    m_pGround1->setB2Body(groundBody);
    m_pGround1->setPTMRatio(RATIO);
    addChild(m_pGround1,3);
    
}


void HelloWorld::addGround2() {
    m_pGround2 = B2Sprite::create("ground.png");
    CCSize groundSize = m_pGround2->getContentSize();
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = b2Vec2(groundSize.width*3/2.0f/RATIO,
                              groundSize.height/2.0f/RATIO);
    b2Body *groundBody = mWorld->CreateBody(&bodyDef);

    b2PolygonShape groundShape;
    groundShape.SetAsBox(groundSize.width/2.0f/RATIO, groundSize.height/2.0f/RATIO);
    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &groundShape;
    groundBody->CreateFixture(&groundFixtureDef);
    
    m_pGround2->setB2Body(groundBody);
    m_pGround2->setPTMRatio(RATIO);
    addChild(m_pGround2,3);
    
}

void HelloWorld::addBackGround() {
  CCAssert(CCLayer::init(), "");  
      
    // 设置背景,交替变换,全部相加要大于分辨率  
    m_pBackGround1 = CCSprite::create("daybackground.png");    
    m_pBackGround2 = CCSprite::create("daybackground.png");   
    CCAssert(m_pBackGround1 && m_pBackGround2, "");  
    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCRect rcBounding = m_pBackGround1->boundingBox();  
    m_pBackGround1->setPosition(ccp(rcBounding.size.width / 2, size.height / 2));    // 设置在屏幕中间  
    m_pBackGround2->setPosition(ccp(rcBounding.size.width * 3 / 2, size.height / 2));// 设置精灵2连接在精灵1的后面
    this->addChild(m_pBackGround1, 1);    // CHILD_ORDER_BACKGROUND精灵的层级，这里是 = 1  
    this->addChild(m_pBackGround2, 1);   
    
}


//增加柱子容器
void HelloWorld::addBarContainer() {
    mBarContainer = CCSprite::create();
    addChild(mBarContainer,2);
}

//容器中放柱子
void HelloWorld::addBar(float dt){
    float offset = -rand()%2;
    float speed = 0;
    // 下面的柱子
    B2Sprite *downBar = B2Sprite::create("down_bar.png");
    CCSize downBarSize = downBar->getContentSize();
    
    b2BodyDef downBarBodyDef;
    downBarBodyDef.type = b2_kinematicBody;
    downBarBodyDef.position = b2Vec2(mScreenSize.width/RATIO+2,
                                     downBarSize.height/RATIO/2+offset);
    downBarBodyDef.linearVelocity = b2Vec2(speed, 0);
    b2Body *downBarBody = mWorld->CreateBody(&downBarBodyDef);
    
    b2PolygonShape downBarShape;
    downBarShape.SetAsBox(downBarSize.width/2/RATIO,
                          downBarSize.height/2/RATIO);
    b2FixtureDef downBarFixtureDef;
    downBarFixtureDef.shape = &downBarShape;
    downBarBody->CreateFixture(&downBarFixtureDef);
    
    downBar->setB2Body(downBarBody);
    downBar->setPTMRatio(RATIO);
    mBarContainer-> addChild(downBar,1,SPRITE_TAG_BAR);

    
    //上面的柱子
    B2Sprite *upBar = B2Sprite::create("up_bar.png");
    CCSize upBarSize = upBar->getContentSize();
    
    b2BodyDef upBarBodyDef;
    upBarBodyDef.type = b2_kinematicBody;
    upBarBodyDef.position = b2Vec2(mScreenSize.width/RATIO+2,
                                   downBarSize.height/RATIO+offset+2+upBarSize.height/2/RATIO);
    upBarBodyDef.linearVelocity = b2Vec2(speed, 0);
    b2Body *upBarDody = mWorld->CreateBody(&upBarBodyDef);
    
    b2PolygonShape upBarShape;
    upBarShape.SetAsBox(upBarSize.width/2/RATIO, upBarSize.height/2/RATIO);
    b2FixtureDef upBarFixtureDef;
    upBarFixtureDef.shape = &upBarShape;
    upBarDody->CreateFixture(&upBarFixtureDef);
    
    upBar->setB2Body(upBarDody);
    upBar->setPTMRatio(RATIO);
    mBarContainer->addChild(upBar,1,SPRITE_TAG_BAR);
}

void HelloWorld::update(float dt){
    //重力响应
    mWorld->Step(dt, 8, 3); // 8和3为官方推荐数据
    if (myangle++<20)
    {
		mBird->setRotation(myangle);
    }
	else
	{
		if(mBird->getRotation() > -91)
			mBird->setRotation(mBird->getRotation()-2);
	}
	if(myflag==1)
	{
		mBird->setRotation(-90);
		return;
	}
	m_pBackGround1->setPositionX(m_pBackGround1->getPositionX() - 1);    // 每次update都向左移动1点  
    m_pBackGround2->setPositionX(m_pBackGround2->getPositionX() - 1);  
    CCRect rcBounding1 = m_pBackGround1->boundingBox();  
    CCRect rcBounding2 = m_pBackGround2->boundingBox();  
	CCLOG("rcBounding1 MinX:%d MinY:%d MaxX:%d MaxY:%d", rcBounding1.getMinX()
		, rcBounding1.getMinY(), rcBounding1.getMaxX(), rcBounding1.getMaxY());
    if (rcBounding1.getMaxX() <= 0)    // 如果完全消失在屏幕上，就移动精灵1到精灵3的后面  
    {  
        m_pBackGround1->setPositionX(rcBounding1.size.width * 3 / 2);  
    }  
    if (rcBounding2.getMaxX() <= 0)    // 如果完全消失在屏幕上，就移动精灵2到精灵1的后面  
    {  
        m_pBackGround2->setPositionX(rcBounding2.size.width * 3 / 2);  
    }  
	
	m_pGround1->setPositionX(m_pGround1->getPositionX() - 1);    // 每次update都向左移动1点  
    m_pGround2->setPositionX(m_pGround2->getPositionX() - 1);  
    CCRect rcGroundBounding1 = m_pGround1->boundingBox();  
    CCRect rcGroundBounding2 = m_pGround2->boundingBox();  

	//地面移动
	if (rcGroundBounding1.getMaxX() <= 0)    // 如果完全消失在屏幕上，就移动精灵1到精灵3的后面  
    {  
        m_pGround1->setPositionX(rcGroundBounding1.size.width * 3 / 2);  
    }  
    if (rcGroundBounding2.getMaxX() <= 0)    // 如果完全消失在屏幕上，就移动精灵2到精灵1的后面  
    {  
        m_pGround2->setPositionX(rcGroundBounding2.size.width * 3 / 2);  
    }
    CCSprite *s;
    std::vector<b2Body *>toDestroy;
    for(b2Body *b = mWorld->GetBodyList(); b != NULL; b = b->GetNext()){
            s = (CCSprite *)b->GetUserData();
			if(s != NULL && s->getTag()==SPRITE_TAG_BAR){	
				s->setPositionX(s->getPositionX() - 1);
				if(s->getPositionX() < -20){
					toDestroy.push_back(b);
					s->removeFromParent();
					mWorld->DestroyBody(b);
				    b = mWorld->GetBodyList();
			}
        }
    }

	
    /*std::vector<b2Body*>::iterator pos2;
    for (pos2 = toDestroy.begin();pos2!=toDestroy.end();++pos2)
    {
        b2Body* body = *pos2;
        if(body->GetUserData()!=NULL)
        {
            CCSprite* sprite = (CCSprite*)body->GetUserData();
            this->removeChild(sprite,true);
        }
        
        mWorld->DestroyBody(body);
        body = NULL;

    }*/
 
}

void HelloWorld::BeginContact(b2Contact *contact){
    if(contact->GetFixtureA()->GetBody()->GetUserData() == m_pGround1 ||
		contact->GetFixtureB()->GetBody()->GetUserData() == m_pGround1 ||
		contact->GetFixtureA()->GetBody()->GetUserData() == m_pGround2 ||
		contact->GetFixtureB()->GetBody()->GetUserData() == m_pGround2 )
	{
		
		CCMessageBox("Game Over!", "Game Over!");
		stopGame();
		
	}
		if(contact->GetFixtureA()->GetBody()->GetUserData() == mBird ||
       contact->GetFixtureB()->GetBody()->GetUserData() == mBird){

		mBird->getB2Body()->SetLinearVelocity(b2Vec2(0, -15));
		myflag=1;
        //stopGame();
       // CCMessageBox("Game Over!", "Game Over!");
    }
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	EFFECT_PLAY(true,MUSIC_JUMP);
	//MUSIC_PLAY(MUSIC_JUMP);
	//播放子弹射出去的声音
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MUSIC_JUMP);
    mBird->getB2Body()->SetLinearVelocity(b2Vec2(0.0f, 10.0f));
	mBird->setRotation(0);
	myangle=0;
	
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
