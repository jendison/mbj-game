#include "cocos-ext.h"
#include "WelcomeScene.h"
#include "GameWorld.h"
#include "Macro.h"
#include "gui.h"
#include "CocoStudio/GUI/System/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define CCSSceneReader SceneReader
WelcomeScene::~WelcomeScene()
{
	CC_SAFE_RELEASE(m_pCurNode);
}

bool WelcomeScene::init( )
{
	do 
	{
		CCNode *pNode = CCSSceneReader::sharedSceneReader()->createNodeWithSceneFile("scene/NewProject.json");
		CC_BREAK_IF(!pNode);

		addChild(pNode);
		//scheduleUpdate();

		CCNode* p = pNode->getChildByTag(EGT_Welcome);

		CCComRender* pCom = dynamic_cast<CCComRender*>(p->getComponent("welcomeGUI"));
		CC_BREAK_IF(!pCom);

		UILayer* m_pUI = dynamic_cast<UILayer*>(pCom->getNode());

		UIWidget* pRoot = m_pUI->getWidgetByTag(1);
		CC_BREAK_IF(!pRoot);

		UIButton* pStart =   dynamic_cast<UIButton*>(pRoot->getChildByName("start"));
		CC_BREAK_IF(!pStart);
		pStart->addTouchEventListener(this, toucheventselector(WelcomeScene::menuStartCallback));


		//UIButton* test =   dynamic_cast<UIButton*>(pRoot->getChildByName("Button"));
		//CC_BREAK_IF(!test);
		//test->addReleaseEvent(this, coco_releaseselector(WelcomeScene::menuTestCallback));
		//test->setTouchEnabled(true);
		//test->setTouchEnabled(true);


		//UIButton* pDeveloper =   dynamic_cast<UIButton*>(pRoot->getChildByName("TextButton"));
		//CC_BREAK_IF(!pDeveloper);
		////pDeveloper->addReleaseEvent(this, coco_releaseselector(WelcomeScene::menuDeveloperCallback));
		//pDeveloper->setTouchEnabled(true);


		//UIButton* pexit =   dynamic_cast<UIButton*>(pRoot->getChildByName("exit"));
		//CC_BREAK_IF(!pexit);
		////pexit->addReleaseEvent(this, coco_releaseselector(WelcomeScene::menuExitCallback));

		m_pCurNode = pNode;
		m_pCurNode->retain();
		return true;
	} while (0);

	return false;
}

WelcomeScene* WelcomeScene::create( )
{
	WelcomeScene* pWelcome = new WelcomeScene();
	if (pWelcome && pWelcome->init())
	{
		pWelcome->autorelease();
		return pWelcome;
	}

	delete pWelcome;
	pWelcome = NULL;

	return NULL;
}

void WelcomeScene::menuStartCallback(CCObject* pSender, TouchEventType eType)
{
	if (eType != TouchEventType::TOUCH_EVENT_ENDED)
	{
		return;
	}

	GAMEWORLD->Init();
}

void WelcomeScene::menuDeveloperCallback( CCObject* pSender )
{
	/*CCScene * pScene = CCScene::create();
	CCLayer * pLayer = startUILayer::create();
	pScene->addChild(pLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);*/

	//	cocos2d::CCScene* pBigworld = BigWorldScene::scene();
	//if (pBigworld)
	//{
	//	CCDirector *pDirector = CCDirector::sharedDirector();
	//	pDirector->pushScene(CCTransitionMoveInR::create(1, pBigworld));
	//}
}

void WelcomeScene::menuExitCallback( CCObject* pSender )
{
	//ÍË³öÓÎÏ·
	GAMEWORLD->Stop();
	CCDirector::sharedDirector()->end();
}
void WelcomeScene::menuTestCallback(CCObject* pSender)
{
	/*  CCScene * pScene = CCScene::create();
	CCLayer * pLayer = UILayerStart::create();
	pScene->addChild(pLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);*/
}

