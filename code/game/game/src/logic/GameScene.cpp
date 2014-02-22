#include "GameScene.h"
#include "GameBattleLayer.h"

#include <cocos2d.h>
#include <cocos-ext.h>
#include "../template/TemplateMgr.h"
#include "../template/TemplateScene.h"
#include "GameWorld.h"
#include "Macro.h"
#include "UILayerGameBattle.h"

using namespace cocos2d;
using namespace cocos2d::extension;


GameScene::GameScene() : m_pBattleLayer(NULL), m_pUIBattleLayer(NULL), m_nSN(0)
{
	GAMEWORLD->setCurrentScene(this);
}


GameScene::~GameScene()
{

}


GameScene* GameScene::create(int32t nSN)
{
	GameScene* pScene = new GameScene();
	if (pScene && pScene->init(nSN))
	{
		pScene->autorelease();
		return pScene;
	}

	CC_SAFE_DELETE(pScene);
	return NULL;
}

bool GameScene::init(int32t nSN)
{
	do 
	{	
		m_nSN = nSN;

		//加载资源
		CC_BREAK_IF(!LoadResource());

		CC_BREAK_IF(!loadMap());

		//加载游戏层
		m_pBattleLayer = GameBattleLayer::create();
		CC_BREAK_IF(!m_pBattleLayer);
		addChild(m_pBattleLayer);
		m_pBattleLayer->setContentSize(getContentSize());

		//加载UI层
		CC_BREAK_IF(!loadMainUI());

		return true;
	} while (0);

	return false;
}

bool GameScene::loadMainUI()
{
	m_pUIBattleLayer = UILayerGameBattle::create();
	GAME_ASSERT_RET(m_pUIBattleLayer, false, ("init UILayerGameBattle fail"));
	addChild(m_pUIBattleLayer);
	return true;
}

bool GameScene::loadMap()
{
	const TemplateScene* pTempScene = GAMEWORLD->get<TemplateScene>(m_nSN);
	GAME_ASSERT_RET(pTempScene, false, ( "read template scene fail"));

	int32t m_nRes= pTempScene->getInitres();
	m_nNextScene = pTempScene->getNextscene();

	//读取地图文件
	m_pMap = CCTMXTiledMap::create(pTempScene->getMapfile().c_str());
	GAME_ASSERT_RET(m_pMap, false, ( "read map fail"));

	m_nNextScene = pTempScene->getNextscene();
	CCSize mapSize = m_pMap->getMapSize();
	CCSize tileSize = m_pMap->getTileSize();
	this->setContentSize(CCSizeMake(mapSize.width * tileSize.width, mapSize.height * tileSize.height));

	CCTMXObjectGroup* pGroup = m_pMap->objectGroupNamed("camp");
	GAME_ASSERT_RET(pGroup, false, ( "load camp from map fail"));

	m_ptSpritePlayer[TAimMoveType_floor].x  = pGroup->objectNamed("campA_floor")->valueForKey("x")->floatValue();
	m_ptSpritePlayer[TAimMoveType_floor].y  = pGroup->objectNamed("campA_floor")->valueForKey("y")->floatValue();
	m_ptSpritePlayer[TAimMoveType_sky].x  = pGroup->objectNamed("campA_sky")->valueForKey("x")->floatValue();
	m_ptSpritePlayer[TAimMoveType_sky].y  = pGroup->objectNamed("campA_sky")->valueForKey("y")->floatValue();

	m_ptSpriteAI[TAimMoveType_floor].x  = pGroup->objectNamed("campB_floor")->valueForKey("x")->floatValue();
	m_ptSpriteAI[TAimMoveType_floor].y  = pGroup->objectNamed("campB_floor")->valueForKey("y")->floatValue();
	m_ptSpriteAI[TAimMoveType_sky].x  = pGroup->objectNamed("campB_sky")->valueForKey("x")->floatValue();
	m_ptSpriteAI[TAimMoveType_sky].y  = pGroup->objectNamed("campB_sky")->valueForKey("y")->floatValue();

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pTempScene->getBgmusic().c_str(), true);

	addChild(m_pMap, -1);
	return true;
}

void GameScene::loadArmature( const char* str )
{
	CCString* strPng = CCString::createWithFormat("%s0.png", str);
	CCString* strPList = CCString::createWithFormat("%s0.plist", str);
	CCString* strPExportJson = CCString::createWithFormat("%s.ExportJson", str);
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(strPng->getCString(), strPList->getCString(), strPExportJson->getCString());
}

bool GameScene::LoadResource()
{
	//sprite
	//loadArmature("sprite/core_ai");
	//loadArmature("sprite/core_player");
	//loadArmature("sprite/hero");
	//loadArmature("sprite/shibing1");
	//loadArmature("sprite/shibing2");
	//loadArmature("sprite/shibing3");
	//loadArmature("sprite/nongchangzhu");
	//loadArmature("sprite/mache");
	//loadArmature("sprite/reqiqiu");
	loadArmature("sprite/niuzai");

	//skill
	loadArmature("skill/dandao");
	loadArmature("skill/dandao1");
	loadArmature("skill/diyu");
	loadArmature("skill/hit");
	loadArmature("skill/hit1");
	loadArmature("skill/light");
	loadArmature("skill/light1");

	return true;
}

void GameScene::onEnter()
{
	CCScene::onEnter();
}
