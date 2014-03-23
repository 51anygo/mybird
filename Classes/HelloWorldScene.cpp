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
#include "ShowNumberNode.h"
#include "SGPlayMusic.h"
USING_NS_CC;
//clone Flappy Bird
//http://comandobueiro.com.br/flappy-bird-clone-com-appcelerator-e-lanica.html
//http://lanica.co/flappy-clone/
//图片去底
//http://www.2gei.com/bgremover




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

	mScreenSize = CCDirector::sharedDirector()->getWinSize();
	mfac=CCDirector::sharedDirector()->getContentScaleFactor();
	initWorld();	
	for (int i = 0; i<GBACKGROUNDNUM; i++)
	{
		addBackGround(i);
	}
	int imaxgroundnum=1;
	for (int i = 0; i<imaxgroundnum; i++)
	{
		imaxgroundnum=addGround(i);
	}
	m_ilastground=imaxgroundnum-1;
	CCLOG("m_pLastGround->boundingBox() first x:%f,:%f  ", (m_pGroundVec[m_ilastground])->boundingBox().getMaxX(),
		(m_pGroundVec[m_ilastground])->boundingBox().size.width);
	addStart();
	addTop();
	addRate();
	addFlappyBird();
	addBird();
	addBarContainer();
	//计分板
	addNumberNode();
	setTouchEnabled(true);
	myflag=0;
	m_istatus=GETREAD;
	//scheduleOnce(schedule_selector(HelloWorld::startGame), 1);
	this->scheduleUpdate();
	//创建动画
	initAction();
	return true;
}

void HelloWorld::startGame(float dt){
	m_pStart->setVisible(false);
	m_pTop->setVisible(false);
	m_pRate->setVisible(false);
	m_pFlappyBird->setVisible(false);
	m_istatus=RUNNING;
	//scheduleUpdate();
	schedule(schedule_selector(HelloWorld::addBar), 2);
}

void HelloWorld::stopGame(){
	unscheduleUpdate();
	unschedule(schedule_selector(HelloWorld::addBar));
}

void HelloWorld::initWorld(){
	mWorld = new b2World(b2Vec2(0, gDownVelocity));
	mWorld->SetContactListener(this);
}
//http://blog.csdn.net/farsa/article/details/9430155
void HelloWorld::addNumberNode()  
{  
	testnum=0;
	ShowNumberNode * snn = ShowNumberNode::CreateShowNumberNode("menu_num.png", 923, 22/mfac, 30/mfac  );  
	snn->f_ShowNumber(testnum);  
	snn->setPosition(ccp(mScreenSize.width/2,mScreenSize.height-50));  
	this->addChild(snn,5,0);  
	//schedule(schedule_selector(HelloWorld::logic), 2.0f);  

}  

void HelloWorld::logic(float dt)
{
	ShowNumberNode * snn = (ShowNumberNode *)this->getChildByTag(0);
	snn->f_ShowNumber(testnum );
	testnum = testnum +1;


}

//number png http://i.pku.edu.cn/trac/bazinga/changeset/117/
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



void HelloWorld::addStart() {
	m_pStart = CCSprite::create("start.png");     
	CCRect rcBounding = m_pStart->boundingBox();
	CCSize startSize = m_pStart->getContentSize();
	float fStartWidth=rcBounding.size.width/2.0f;
	float fStartHeight=rcBounding.size.height/2.0f;
	//m_pStart->setPosition(ccp(this->mScreenSize.width/2.0f/RATIO-(fStartWidth/2.0f), 
	//	groundSize.height/2.0f/RATIO+(fStartHeight/2.0f)));    // 设置在屏幕中间  
	float xpos=mScreenSize.width/2.0f-fStartWidth;
	float ypos=m_pGroundVec[0]->boundingBox().getMaxY()+fStartHeight;
	//xpos-=rcBounding.size.width/2.;
	m_pStart->setPosition(ccp(xpos,  ypos));    // 设置在屏幕中间  
	this->addChild(m_pStart,SPRITE_TAG_CHAR);    // CHILD_ORDER_BACKGROUND精灵的层级，这里是 = 1  

}


void HelloWorld::addFlappyBird() {
	m_pFlappyBird = CCSprite::create("flappybird.png");     
	CCRect rcBounding = m_pFlappyBird->boundingBox();
	float fFlappyBirdHeight=rcBounding.size.height/2.0f;
	float xpos=mScreenSize.width/2;
	float ypos=mScreenSize.height/2+fFlappyBirdHeight+30;

	m_pFlappyBird->setPosition(ccp(xpos,  ypos));    // 设置在屏幕中间  
	this->addChild(m_pFlappyBird, SPRITE_TAG_CHAR);  

}

void HelloWorld::addRate() {
	m_pRate = CCSprite::create("rate.png");     
	CCRect rcBounding = m_pRate->boundingBox();
	CCSize startSize = m_pRate->getContentSize();
	float fRateWidth=rcBounding.size.width/2.0f;
	float fRateHeight=rcBounding.size.height/2.0f;
	//m_pStart->setPosition(ccp(this->mScreenSize.width/2.0f/RATIO-(fStartWidth/2.0f), 
	//	groundSize.height/2.0f/RATIO+(fStartHeight/2.0f)));    // 设置在屏幕中间  
	float xpos=mScreenSize.width/2.0f;
	float ypos=m_pTop->boundingBox().getMaxY()+fRateHeight+10;
	//xpos-=rcBounding.size.width/2.;
	m_pRate->setPosition(ccp(xpos,  ypos));    // 设置在屏幕中间  
	this->addChild(m_pRate, SPRITE_TAG_CHAR);  


}

void HelloWorld::addTop() {
	CCSize groundSize = m_pGroundVec[0]->getContentSize();
	m_pTop = CCSprite::create("top.png");     
	CCRect rcBounding = m_pTop->boundingBox();
	CCSize startSize = m_pTop->getContentSize();
	float fTopWidth=rcBounding.size.width/2.0f;
	float fTopHeight=rcBounding.size.height/2.0f;
	//m_pStart->setPosition(ccp(this->mScreenSize.width/2.0f/RATIO-(fStartWidth/2.0f), 
	//	groundSize.height/2.0f/RATIO+(fStartHeight/2.0f)));    // 设置在屏幕中间  
	float xpos=mScreenSize.width/2.0f+fTopWidth+10;
	float ypos=m_pGroundVec[0]->boundingBox().getMaxY()+fTopHeight;
	//xpos-=rcBounding.size.width/2.;
	m_pTop->setPosition(ccp(xpos,  ypos));    // 设置在屏幕中间  
	this->addChild(m_pTop, SPRITE_TAG_CHAR);    // CHILD_ORDER_BACKGROUND精灵的层级，这里是 = 1  

}

void HelloWorld::addGameOver() {

	m_pAddGameOver = CCSprite::create("GameOver.png");      
	CCRect rcBounding = m_pAddGameOver->boundingBox();  
	m_pAddGameOver->setPosition(ccp(rcBounding.size.width / 2, rcBounding.size.height / 2));    // 设置在屏幕中间  
	this->addChild(m_pAddGameOver, 1);    // CHILD_ORDER_BACKGROUND精灵的层级，这里是 = 1  

}

void HelloWorld::addBird(){
	mBird = B2Sprite::create("bird.png");

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	// 单位为 米
	//bodyDef.position = b2Vec2(mScreenSize.width*gBirdX/RATIO, mScreenSize.height*gBirdY/RATIO); // 10m以内模拟效果较高效。
	bodyDef.position = b2Vec2(mScreenSize.width*gBirdX/RATIO, mScreenSize.height*gBirdY/RATIO); // 10m以内模拟效果较高效。
	b2Body *birdBody = mWorld->CreateBody(&bodyDef);

	// 碰撞
	CCSize birdSize = mBird->getContentSize();
	b2PolygonShape birdShape;
	birdShape.SetAsBox(birdSize.width/2.0f/RATIO, birdSize.height/2.0f/RATIO); // 半宽，半高

	b2FixtureDef birdFixtureDef;
	birdFixtureDef.shape = &birdShape;
	birdFixtureDef.filter.maskBits = 0x0006;
	birdBody->CreateFixture(&birdFixtureDef);

	mBird->setPTMRatio(RATIO);
	mBird->setB2Body(birdBody);
	addChild(mBird,4);

}
//1 2 4 6
//0 1 2 3
int HelloWorld::addGround(int index) {
	B2Sprite* pGround = B2Sprite::create("ground.png");
	CCSize groundSize = pGround->getContentSize();
	//m_pGround[index]->setTag(index);
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	bodyDef.position = b2Vec2((groundSize.width*(index*2)/2.0f)/RATIO,
		groundSize.height/2.0f/RATIO);

	b2Body *groundBody = mWorld->CreateBody(&bodyDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(groundSize.width/2.0f/RATIO, groundSize.height/2.0f/RATIO);
	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &groundShape;
	groundFixtureDef.filter.categoryBits = 0x0002;
	groundBody->CreateFixture(&groundFixtureDef);

	pGround->setB2Body(groundBody);
	pGround->setPTMRatio(RATIO);
	addChild(pGround,3,SPRITE_TAG_GROUND);
	m_pGroundVec.push_back(pGround);
	int iwin=int(mScreenSize.width/(groundSize.width)+2);
	CCLOG("addGround win x:%f,groundSize.width:%f,mfac:%f,iwin:%d",mScreenSize.width,
		groundSize.width,mfac,iwin);
	return iwin;

}



void HelloWorld::addBackGround(int index) {

	// 设置背景,交替变换,全部相加要大于分辨率  
	m_pBackGround[index] = CCSprite::create("daybackground.png");     
	CCSize size = CCDirector::sharedDirector()->getWinSize();  
	CCRect rcBounding = m_pBackGround[index]->boundingBox();  
	m_pBackGround[index]->setPosition(ccp(rcBounding.size.width*(index*2+1) / 2, size.height / 2));    // 设置在屏幕中间  
	this->addChild(m_pBackGround[index], 1);    // CHILD_ORDER_BACKGROUND精灵的层级，这里是 = 1  


}


//增加柱子容器
void HelloWorld::addBarContainer() {
	mBarContainer = CCSprite::create();
	addChild(mBarContainer,2);
}

//容器中放柱子
void HelloWorld::addBar(float dt){
	float offset = -rand()%6;
	float speed = 0;
	// 下面的柱子
	B2Sprite *downBar = B2Sprite::create("down_bar.png");
	CCSize downBarSize = downBar->getContentSize();


	b2BodyDef downBarBodyDef;
	downBarBodyDef.type = b2_kinematicBody;
	//x轴屏幕右方外两像素的位置,y轴是柱子一半
	downBarBodyDef.position = b2Vec2(mScreenSize.width/RATIO+2,
		downBarSize.height/RATIO/2+offset);
	downBarBodyDef.linearVelocity = b2Vec2(speed, 0);
	b2Body *downBarBody = mWorld->CreateBody(&downBarBodyDef);
	b2PolygonShape downBarShape;
	downBarShape.SetAsBox(downBarSize.width/2/RATIO,
		downBarSize.height/2/RATIO);
	b2FixtureDef downBarFixtureDef;
	downBarFixtureDef.shape = &downBarShape;
	downBarFixtureDef.filter.categoryBits = 0x0004;
	downBarBody->CreateFixture(&downBarFixtureDef);

	downBar->setB2Body(downBarBody);
	downBar->setPTMRatio(RATIO);
	mBarContainer-> addChild(downBar,1,SPRITE_TAG_BAR);
	mapbar.insert(make_pair(downBar,0));

	//上面的柱子
	B2Sprite *upBar = B2Sprite::create("up_bar.png");
	CCSize upBarSize = upBar->getContentSize();

	b2BodyDef upBarBodyDef;
	upBarBodyDef.type = b2_kinematicBody;
	upBarBodyDef.position = b2Vec2(mScreenSize.width/RATIO+2,
		downBarSize.height/RATIO+offset+gBardis+upBarSize.height/2/RATIO);
	upBarBodyDef.linearVelocity = b2Vec2(speed, 0);
	b2Body *upBarDody = mWorld->CreateBody(&upBarBodyDef);
	b2PolygonShape upBarShape;
	upBarShape.SetAsBox(upBarSize.width/2/RATIO, upBarSize.height/2/RATIO);
	b2FixtureDef upBarFixtureDef;
	upBarFixtureDef.shape = &upBarShape;
	upBarFixtureDef.filter.categoryBits = 0x0004;
	upBarDody->CreateFixture(&upBarFixtureDef);
	upBar->setB2Body(upBarDody);
	upBar->setPTMRatio(RATIO);
	mBarContainer->addChild(upBar,1,SPRITE_TAG_BAR);
}

void HelloWorld::update(float dt){
	if(m_istatus!=GAMEOVER){
		int lastgroud=-1;
		for (int i=0; i<m_pGroundVec.size(); i++)
		{
			m_pGroundVec[i]->setPositionX(m_pGroundVec[i]->getPositionX() - MOVESPEED);
			CCRect rcGroundBounding = m_pGroundVec[i]->boundingBox(); 
			if (rcGroundBounding.getMaxX()<=0)
			{
				lastgroud=i;			
			}
		}
		//float groundsize = m_pGround[i]->getContentSize().width*1.0;
		//m_pGround[i]->setPositionX(groundsize/2. + (GGROUNDNUM-1)*groundsize);
		if(lastgroud>-1){
			float moveposx=m_pGroundVec[m_ilastground]->boundingBox().getMaxX();
			moveposx+=m_pGroundVec[lastgroud]->getContentSize().width/2.;
			m_pGroundVec[lastgroud]->setPositionX(moveposx);
			m_ilastground=lastgroud;
			CCLOG("win x:%f,Ground x:%f,mfac:%f,index=%d ",this->mScreenSize.width,
				moveposx,mfac,m_ilastground);
		}
		
	}
	if(m_istatus==GETREAD ){
		return;
	}
	//重力响应
	mWorld->Step(dt, 8, 3); // 8和3为官方推荐数据
	if (myangle++<25)
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
	/*for (int i=0; i<gbackgroundNum; i++)
	{
	m_pBackGround[i]->setPositionX(m_pBackGround[i]->getPositionX() - 1); 
	CCRect rcBounding = m_pBackGround[i]->boundingBox(); 
	if (rcBounding.getMaxX() <= 0)    // 如果完全消失在屏幕上，就移动精灵1到精灵3的后面  
	{  
	int backgroundsize = m_pBackGround[i]->getContentSize().width;
	m_pBackGround[i]->setPositionX(backgroundsize/2 + (ggroundNum-1)*backgroundsize);  
	}  

	}
	*/

	//CCLOG("rcBounding1 MinX:%d MinY:%d MaxX:%d MaxY:%d", rcBounding1.getMinX()
	//, rcBounding1.getMinY(), rcBounding1.getMaxX(), rcBounding1.getMaxY());



	CCSprite *s;
	std::vector<b2Body *>toDestroy;
	map<CCSprite *,int>::iterator itbar;
	for(b2Body *b = mWorld->GetBodyList(); b != NULL; b = b->GetNext()){
		s = (CCSprite *)b->GetUserData();
		if(s != NULL && s->getTag()==SPRITE_TAG_BAR){
			itbar=mapbar.find(s);
			if(itbar!=mapbar.end() && itbar->second==0 && itbar->first->boundingBox().getMinX() <= this->mBird->boundingBox().getMaxX())
			{
				ShowNumberNode * snn = (ShowNumberNode *)this->getChildByTag(0);
				snn->f_ShowNumber(++testnum);
				itbar->second=1;
				mapbar.erase(itbar);
			}
			//CCLOG("bird x:%f guan x:%f ", mBird->getPositionX(),s->getPositionX());

			s->setPositionX(s->getPositionX() - 3);
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
	B2Sprite *p = (B2Sprite *)contact->GetFixtureA()->GetBody()->GetUserData();
	if(p->getTag()==SPRITE_TAG_GROUND)
	{

		CCMessageBox("Game Over!", "Game Over!");
		stopGame();

	}
	if(p == mBird || p == mBird){
		mBird->getB2Body()->SetLinearVelocity(b2Vec2(0, gUpVelocity));
		myflag=1;
		b2Filter myfilter;
		myfilter.maskBits=0x0002;
		mBird->getB2Body()->GetFixtureList()->SetFilterData(myfilter);
		//stopGame();
		// CCMessageBox("Game Over!", "Game Over!");
	}
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	CCLOG("win x:%f,Ground x:%f,mfac:%f,index=%d ",this->mScreenSize.width,
				m_pGroundVec[m_ilastground]->boundingBox().getMaxX(),mfac,m_ilastground);
	static int flag;       
    CCTouch *pTouch = (CCTouch*)pTouches->anyObject();  
    CCPoint click2 = pTouch->getLocation();  
    CCLog("ccTouchesBegan,%d,%f,%f",++flag,click2.x,click2.y); 
	if(this->m_istatus!=RUNNING){
		CCPoint touchPoint = pTouch->getLocationInView();
		touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
		CCRect rect = m_pStart->boundingBox();
		//在判断你点击的这个点touchPoint 是否在图片按钮矩形里面rect ;
	   if(rect.containsPoint(touchPoint))
	   {
		   this->startGame(0);
	   }
			//为true就进来，说明点中在图片按钮矩形里面
			//CCScene* scen = HelloWorld::scene();
			//CCDirector::sharedDirector()->replaceScene(scen);
		return;
	}
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
