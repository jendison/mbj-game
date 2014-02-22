#include "GameWorld.h"
#include "CCPlatformDefine.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "GameBattleLayer.h"
#include "../template/TemplateGame.h"
#include "GameCamp.h"
#include "GameScene.h"

USING_NS_CC;

GameWorld::GameWorld(void)
{
	pTemplateMgr = NULL;
	m_pAICamp = NULL;
	m_pPlayerCamp = NULL;
	m_nIncRes = 0;
	m_pScene = NULL;
}

GameWorld::~GameWorld(void)
{
	CC_SAFE_DELETE(m_pAICamp);
	CC_SAFE_DELETE(m_pPlayerCamp);
	CC_SAFE_DELETE(pTemplateMgr);
	m_pScene = NULL;
}

bool GameWorld::Init()
{
	do 
	{
		const TemplateGame* pTempGame = get<TemplateGame>(1);
		CC_BREAK_IF(!pTempGame);

		m_pAICamp = GameCamp::create(pTempGame->getBcamp());
		CC_BREAK_IF(!m_pAICamp);

		m_pPlayerCamp = GameCamp::create(pTempGame->getAcamp());
		CC_BREAK_IF(!m_pAICamp);

		m_nIncRes = pTempGame->getResincspeed();

		// initialize director
		CCDirector *pDirector = CCDirector::sharedDirector();

		// create a scene. it's an autorelease object
		m_pScene = GameScene::create(pTempGame->getInitscene());

		// run
		pDirector->replaceScene(CCTransitionMoveInR::create(1, m_pScene));
		return true;
	} while (0);

	return false;
}

void GameWorld::Run()
{
	 
}

bool GameWorld::Stop()
{
	return false;
}
