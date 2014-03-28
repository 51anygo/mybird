#include "StartScence.h"

#include "HelloWorldScene.h"


CCScene* Start::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    cocos2d::CCLayer *layer = Start::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Start::init()
{
	CCSize mScreenSize = CCDirector::sharedDirector()->getWinSize();

	for (int i = 0; i<gbackgroundNum; i++)
	{
		CCSprite *pbackGround = CCSprite::create("daybackground.png"); 
		CCRect rcBounding = pbackGround->boundingBox();  
		pbackGround->setPosition(ccp(rcBounding.size.width*(i*2+1) / 2, mScreenSize.height / 2));    
		this->addChild(pbackGround);   
	}
	
	CCSize groundSize;
	for (int i = 0; i<ggroundNum; i++)
	{
		pGround[i] = CCSprite::create("ground.png");
		groundSize = pGround[i]->getContentSize();
		pGround[i]->setPosition(ccp(groundSize.width*(i*2+1) / 2, groundSize.height / 2));    
		this->addChild(pGround[i]);   
	}


	tbBird = CCSprite::create("bird.png");
	tbBird->setPosition(ccp(mScreenSize.width/2,mScreenSize.height/2));
	addChild(tbBird,0);

	CCMenuItemImage *tbstart = CCMenuItemImage::create("start.png", "start.png", this, menu_selector(Start::tbstartCallback) );
	tbstart->setPosition(ccp(mScreenSize.width/4,groundSize.height + 10 + tbstart->getContentSize().height/2));
    CCMenu* pMenu1 =CCMenu::create(tbstart, NULL);

    pMenu1->setPosition( CCPointZero );
   
	addChild(pMenu1);


	CCMenuItemImage *tbscore = CCMenuItemImage::create("top.png", "top.png", this, menu_selector(Start::tbtopCallback) );
	tbscore->setPosition(ccp(mScreenSize.width*3/4,groundSize.height+10 + tbscore->getContentSize().height/2));
    CCMenu* pMenu2 =CCMenu::create(tbscore, NULL);

    pMenu2->setPosition( CCPointZero );
   
	addChild(pMenu2);

	CCSprite *m_pFlappyBird = CCSprite::create("flappybird.png");     
	CCRect rcBounding = m_pFlappyBird->boundingBox();
	float fFlappyBirdHeight=rcBounding.size.height/2.0f;
	float xpos=mScreenSize.width/2;
	float ypos=mScreenSize.height*3/4+20;

	m_pFlappyBird->setPosition(ccp(xpos,  ypos));    // 设置在屏幕中间  
	this->addChild(m_pFlappyBird);  

	CCSprite*m_pRate = CCSprite::create("rate.png");     
	rcBounding = m_pRate->boundingBox();
	CCSize startSize = m_pRate->getContentSize();
	float fRateWidth=rcBounding.size.width/2.0f;
	float fRateHeight=rcBounding.size.height/2.0f;
	xpos=mScreenSize.width/2.0f;
	ypos=tbscore->boundingBox().getMaxY()+fRateHeight+10;
	m_pRate->setPosition(ccp(xpos,  ypos));    // 设置在屏幕中间  
	this->addChild(m_pRate);  

	initAction();
	scheduleUpdate();
	
	CCActionInterval*  actionTo = CCMoveBy::create(0.5, ccp(0, 10));
	CCActionInterval*  actionByBack = actionTo->reverse();

	tbBird->runAction(CCRepeatForever::create(CCSequence::create( actionTo,actionByBack,NULL)));

	
	return true;
}



void Start::tbstartCallback(CCObject * pSender)
{
	
	CCScene *pScene = HelloWorld::scene();
	
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1, pScene));
}

void Start::tbtopCallback(CCObject * pSender)
{

}


void Start::initAction()
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
	tbBird->runAction(CCRepeatForever::create(seq));

}

void Start::update(float dt){

	for (int i=0; i<ggroundNum; i++)
	{
		pGround[i]->setPositionX(pGround[i]->getPositionX() - 3);
		CCRect rcGroundBounding = pGround[i]->boundingBox(); 
		if (rcGroundBounding.getMaxX()<=0)
		{
			int groundsize = pGround[i]->getContentSize().width;
			pGround[i]->setPositionX(groundsize/2 + (ggroundNum-1)*groundsize-5);
		}
	}

}