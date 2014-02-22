#include "GameHero.h"
#include "../template/TemplateHero.h"
#include "GameWorld.h"
#include "cocoa/CCGeometry.h"
#include "GameBattleLayer.h"
#include "GameScene.h"
#include "Macro.h"
using namespace cocos2d;

GameHero::GameHero() : GameSprite(), m_bIsCanRun(false),m_nMoney(0), m_nEnery(0)
{
}

GameHero::~GameHero()
{

}

GameHero* GameHero::create( int32t nSN, GameBattleLayer* pGame )
{
	GameHero* pHero = new GameHero();
	if (pHero && pHero->initWithGame(nSN,  pGame))
	{
		pHero->autorelease();
		return pHero;
	}

	CC_SAFE_DELETE(pHero);
	return NULL;
}

bool GameHero::initWithGame( int32t nSN, GameBattleLayer* pGame )
{
	GameWorld* pGameWorld = GAMEWORLD;
	const TemplateHero* pHero = pGameWorld->get<TemplateHero>(nSN);
	GAME_ASSERT_RET(pHero, false, ( "get hero by sn fail"));

	bool r = GameSprite::initWithGame(pHero->getArm());
	GAME_ASSERT_RET(r,false, ("init game sprite fail, when create hero"));
	return r;
}

void GameHero::update( float delta )
{
	GameSprite::update(delta);
}

void GameHero::flowBy( cocos2d::CCNode* pNode )
{
	GameScene* pScene = GAMESCENE;
	CCSize mapSize = pScene->getMapSize();
	CCSize tileSize = pScene->getTileSize();
	CCFollow* pAction = cocos2d::CCFollow::create(this, CCRectMake(0,0, mapSize.width * tileSize.width, mapSize.height * tileSize.height));
	pAction->setTag(GameBattleLayer::EHelloWorldActionTag_FollowHero);
	pNode->runAction(pAction);
}

void GameHero::releaseFlow( cocos2d::CCNode* pNode )
{
	pNode->stopActionByTag(GameBattleLayer::EHelloWorldActionTag_FollowHero);
}

