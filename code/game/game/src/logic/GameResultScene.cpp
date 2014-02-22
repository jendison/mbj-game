#include "GameResultScene.h"
#include "GameBattleLayer.h"
#include "GameScene.h"
#include "Macro.h"
#include "GameWorld.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define CCSSceneReader SceneReader
bool GameResultScene::init(ESpriteCamp eCamp)
{
	do 
	{
		CCNode *pNode = CCSSceneReader::sharedSceneReader()->createNodeWithSceneFile("scene/game_result.json");
		CC_BREAK_IF(!pNode);

		addChild(pNode);
		scheduleUpdate();

		CCNode* p = pNode->getChildByTag(10008);

		CCComRender* pCom = dynamic_cast<CCComRender*>(p->getComponent("GUIComponent"));
		CC_BREAK_IF(!pCom);

		UILayer* m_pUI = dynamic_cast<UILayer*>(pCom->getOwner());

		UIWidget* pRoot = m_pUI->getWidgetByTag(1);
		CC_BREAK_IF(!pRoot);
		bWin = eCamp == ESC_AI;
		UIWidget* pWinfont =  pRoot->getChildByName("winStr");
		CC_BREAK_IF(!pWinfont);
		pWinfont->setVisible(bWin);

		UIWidget* pLosefont = pRoot->getChildByName("loseStr");
		CC_BREAK_IF(!pLosefont);
		pLosefont->setVisible(!bWin);

	} while (0);
	

	return true;
}

GameResultScene* GameResultScene::create(ESpriteCamp eCamp)
{
	GameResultScene* p = new GameResultScene();
	if (p && p->init(eCamp))
	{
		//p->autorelease();
		return p;
	}
	
	delete p;
	p = NULL;
	return NULL;
}

void GameResultScene::changeScene( float dt )
{
	unschedule(schedule_selector(GameResultScene::changeScene));
	GameScene* pScene = GAMESCENE;
	CCDirector::sharedDirector()->replaceScene(CCTransitionSplitCols::create(1, GameScene::create(pScene->getNextSceneSN())));
}

void GameResultScene::update( float dt )
{
	//UIWidget* pRoot = dynamic_cast<UIPanel*>(m_pUI->getWidgetByTag(2));

	//do 
	//{
	//	UIWidget* pWinfont =  pRoot->getChildByName("winStr");
	//	CC_BREAK_IF(!pWinfont);
	//	pWinfont->setVisible(bWin);
	//	
	//	UIWidget* pLosefont = pRoot->getChildByName("loseStr");
	//	CC_BREAK_IF(!pLosefont);
	//	pLosefont->setVisible(!bWin);
	//} while (0);
	
	m_fTimer += dt;
	if (m_fTimer > 5.0f)
	{
		m_fTimer = 0;
		changeScene(0);
	}
}

