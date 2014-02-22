#include <cocos2d.h>
#include "GameBattleLayer.h"
#include "GameAnimation.h"
#include "AppDelegate.h"
#include "GameScene.h"
#include "Macro.h"
#include "LuaHelper.h"
#include "UILayerGameBattle.h"

#include "../logic/GameSprite.h"
#include "../logic/GameWorld.h"
#include "../template/TemplateScene.h"
#include "../template/TemplateArms.h"
#include "../template/TemplateBuilding.h"

#include "../logic/GameCamp.h"
#include "../logic/GameResultScene.h"

using namespace cocos2d;
using namespace cocos2d::extension;

// 校正滑动动画速度
static const int  ADJUST_ANIM_VELOCITY = 800;


GameBattleLayer::GameBattleLayer()
{
	m_pHero = NULL;
	m_aArms = NULL;
	m_aEnemies = NULL;
}

GameBattleLayer::~GameBattleLayer()
{
	CC_SAFE_RELEASE(m_aEnemies);
	CC_SAFE_RELEASE(m_aArms);
}


void GameBattleLayer::onExit()
{
	removeChild(m_pHero);
	m_pHero->release();

	CCObject* pSprite = NULL;
	CCARRAY_FOREACH(m_aEnemies, pSprite){
		GameSprite* pGameSprite = (GameSprite*)pSprite;
		removeChild(pGameSprite);
	}

	pSprite = NULL;
	CCARRAY_FOREACH(m_aArms,pSprite){
		GameSprite* pGameSprite = (GameSprite*)pSprite;
		removeChild(( GameSprite*)pSprite);
	}
}

// on "init" you need to initialize your instance
bool GameBattleLayer::init()
{
    bool bRet = false;
    do 
    {
		CC_BREAK_IF(!CCLayer::init());

		m_aEnemies = CCArray::create();
		m_aEnemies->retain();
		this->loadWave();

		m_aArms = CCArray::create();
		m_aArms->retain();

		CC_BREAK_IF(!this->loadCoreArm(ESC_Player, ESD_Right));
		CC_BREAK_IF(!this->loadCoreArm(ESC_AI, ESD_Left));

		int nHero = CCUserDefault::sharedUserDefault()->getIntegerForKey("hero", 80002);
		CC_BREAK_IF(!this->loadHero(nHero));

		scheduleUpdate();
		schedule(schedule_selector(GameBattleLayer::incRes), 1.0f);

        bRet = true;
    } while (0);

    return bRet;
}




void GameBattleLayer::scrollViewDidZoom( CCScrollView * view )
{

}

void GameBattleLayer::scrollViewDidScroll( cocos2d::extension::CCScrollView * view )
{

}

void GameBattleLayer::onEnter()
{
	CCLayer::onEnter();
	// 这里的第三个参数一定要设置成false，
	// true 即HelloWorld层吞噬掉触摸事件
	// false 即HelloWorld层与CCScrollView对象先后处理触摸事件
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

bool GameBattleLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint ptHero = m_pHero->getSpritePosition();
	m_ptTouch = pTouch->getLocation();
	CCPoint point = getPosition();
	CCPoint ptTouch = convertToNodeSpace(m_ptTouch);
	ESpriteDir eDir = (m_ptTouch.x - point.x) > ptHero.x ? ESD_Right : ESD_Left;

	cocos2d::CCTMXTiledMap* pMap = GAMESCENE->getMap();
	
	m_pHero->setDir(eDir);
	m_pHero->setIsCanRun(true);
	m_pHero->flowBy(pMap);
	m_pHero->flowBy(this);
	return true;
}

void GameBattleLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
}

void GameBattleLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{	
	cocos2d::CCTMXTiledMap* pMap = GAMESCENE->getMap();
	m_pHero->setIsCanRun(false);
	m_pHero->setStatus(ESS_Standing);
	m_pHero->releaseFlow(this);
	m_pHero->releaseFlow(pMap);
}

void GameBattleLayer::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	m_pHero->setIsCanRun(false);
	m_pHero->setStatus(ESS_Standing);
	m_pHero->releaseFlow(this);
}
void GameBattleLayer::update(float dt)
{
	CCPoint ptHero = m_pHero->getSpritePosition();
	CCTMXTiledMap* pMap = GAMESCENE->getMap();

	CCSize mapSize = pMap->getMapSize();
	CCSize tileSize = pMap->getTileSize();
	CCSize screen = CCDirector::sharedDirector()->getWinSize();
	float x = mapSize.width * tileSize.width;
	//调整英雄走到边界的时候 走到点击位置
	if (m_pHero->getDir() == ESD_Right && m_pHero->getStatus() == ESS_Runnig)
	{
		CCPoint ptTouch = convertToNodeSpace(m_ptTouch);

		if ( ptTouch.x < screen.width / 2)
		{
			if (m_pHero->getSpritePositionX() > ptTouch.x)
			{
				m_pHero->setIsCanRun(false);
				m_pHero->setIsCanRun(false);
				m_pHero->setStatus(ESS_Standing);
				m_pHero->releaseFlow(this);
			}
		}

		if ( ptTouch.x > (x - screen.width / 2))
		{
			if (m_pHero->getSpritePositionX() > ptTouch.x)
			{
				m_pHero->setIsCanRun(false);
				m_pHero->setIsCanRun(false);
				m_pHero->setStatus(ESS_Standing);
				m_pHero->releaseFlow(this);
			}
		}
	}
	else if (m_pHero->getDir() == ESD_Left && m_pHero->getStatus() == ESS_Runnig)
	{
		CCPoint ptTouch = convertToNodeSpace(m_ptTouch);

		if ( ptTouch.x < screen.width / 2)
		{
			if (m_pHero->getSpritePositionX() < ptTouch.x)
			{
				m_pHero->setIsCanRun(false);
				m_pHero->setIsCanRun(false);
				m_pHero->setStatus(ESS_Standing);
				m_pHero->releaseFlow(this);
			}
		}

		if ( ptTouch.x > (x - screen.width / 2))
		{
			if (m_pHero->getSpritePositionX() < ptTouch.x)
			{
				m_pHero->setIsCanRun(false);
				m_pHero->setIsCanRun(false);
				m_pHero->setStatus(ESS_Standing);
				m_pHero->releaseFlow(this);
			}
		}
	}
}


void GameBattleLayer::loadWave()
{
	GameWorld* pWorld = GAMEWORLD;
	const TemplateScene* pTempScene = pWorld->get<TemplateScene>(GAMESCENE->getSN());
	GAME_ASSERT_RET(pTempScene, ;, ( "TemplateScene need"));
	const vector<ArmBirthData>&  arms = pTempScene->getArms();

	for (uint32t i = 0; i < arms.size(); ++i)
	{
		const ArmBirthData& armdata = arms[i];
		GameSprite* pSprite1 = createSprite(armdata.arm, ESC_AI, ESD_Left, armdata.time / 1000.0f);
		GAME_ASSERT_RET(pSprite1, ;, ( "create sprite fail"));
		m_aEnemies->addObject(pSprite1);
		addChild(pSprite1);
	}
}

void GameBattleLayer::playerAddSprite(int32t nArmSN)
{
	//扣除资源
	const TemplateArms* pArm = GAMEWORLD->get<TemplateArms>(nArmSN);
	GAME_ASSERT_RET(pArm, ;, ( "invalid arm sn"));
	if (pArm->getCosttype() == TCostType_res)
	{
		int nNum = pArm->getCostnum();
		if (m_nRes < nNum)
		{
			return;
		}

		changeResNum(-nNum);
	}

	GameSprite* pSprite2 = createSprite(nArmSN,ESC_Player, ESD_Right,0.5f);
	GAME_ASSERT_RET(pSprite2, ;, ( "create sprite fail"));
	m_aArms->addObject(pSprite2);
	addChild(pSprite2);
}

GameSprite* GameBattleLayer::selectAim( GameSprite* pSprite, GameSkill* pSkill )
{
	GAME_ASSERT_RET(pSprite, NULL, ( "sprite == null"));
	GAME_ASSERT_RET(pSkill, NULL, ( "pSkill == null"));

	ESpriteCamp eCamp = pSprite->getCamp();

	float fX = pSprite->getSpritePositionX();

	float fSkillDistance = pSkill->getDistance();
	ESpriteDir eDir = pSprite->getDir();
	CCArray* pArr = eCamp == ESC_Player ? m_aEnemies : m_aArms;

	GameSprite* pAim = NULL;
	float fDis = INT_MAX;
	CCObject *pObject = NULL;
	float fTmpDis = fDis;
	const TemplateSkill* pSkillTemp = pSkill->GetTemplate();
	TAOEType eAOEType = pSkillTemp->getAoetype();

	CCARRAY_FOREACH(pArr, pObject)
	{
		GameSprite *enemy = (GameSprite*)pObject;

		if (enemy->isDead())
		{
			continue;
		}

		if (eAOEType == TAOEType_line && enemy->getMoveType() != pSprite->getMoveType())
		{
			continue;
		}

		//只能选取 我朝向方向的敌人
		if (eDir == ESD_Left && fX > enemy->getSpritePositionX())
		{
			fTmpDis = ccpDistance(pSprite->getSpritePosition(), enemy->getSpritePosition());
		}
		else if (eDir == ESD_Right &&  fX < enemy->getSpritePositionX())
		{
			fTmpDis = ccpDistance(pSprite->getSpritePosition(), enemy->getSpritePosition());
		}

		//选择离我最近的
		if (fDis > fTmpDis)
		{
			fDis = fTmpDis;
			pAim = enemy;
		}
	}

	do 
	{
		//AI阵营还要增加英雄判断
		CC_BREAK_IF (eCamp != ESC_AI);

		if (eAOEType == TAOEType_line && m_pHero->getMoveType() != pSprite->getMoveType())
		{
			break;
		}

		if (eDir == ESD_Left && m_pHero->getSpritePositionX() < fX)
		{
			fTmpDis = ccpDistance(pSprite->getSpritePosition(), m_pHero->getSpritePosition());
		}
		else if (eDir == ESD_Right && m_pHero->getSpritePositionX() > fX)
		{
			fTmpDis = ccpDistance(pSprite->getSpritePosition(), m_pHero->getSpritePosition());
		}

		if (fDis > fTmpDis)
		{
			fDis = fTmpDis;
			pAim = m_pHero;
		}

	} while (0);


	//是否在技能施展范围之内？
	if (fDis < fSkillDistance)
	{
		return pAim;
	}

	return NULL;
}

bool GameBattleLayer::loadCoreArm( ESpriteCamp eCamp, ESpriteDir eDir )
{
	GameWorld* pGameWorld = GAMEWORLD;
	GameCamp* pCamp = pGameWorld->getCamp(eCamp);
	GAME_ASSERT_RET(pCamp, false, ( "not init??"));

	do 
	{
		int32t nSN = pCamp->getCoreArm();
		GameSprite* p = createSprite(nSN, eCamp, eDir, 1);
		if (eCamp == ESC_AI)
		{
			m_aEnemies->addObject(p);
		}
		else
		{
			m_aArms->addObject(p);
		}

		addChild(p);

		return true;
	} while (0);

	return false;
}


bool GameBattleLayer::loadHero( int nSN )
{
	GameWorld* pGameWorld = GAMEWORLD;
	GameScene* pScene = GAMESCENE;
	do 
	{
		GameHero* pHero = GameHero::create(nSN, this);
		pHero->setStatus(ESS_Standing);	//站立姿态
		pHero->setDir(ESD_Right);
		pHero->setCamp(ESC_Player);
		pHero->setVisible(false);
		pHero->setSpriteScale(1);
		pHero->schedule(schedule_selector(GameSprite::doActivate), 0.5);
		pHero->setPosition(pScene->getSpritePlayerBronPoint(TAimMoveType_floor));
		pHero->retain();
		m_pHero = pHero;
		addChild(m_pHero);
		return true;
	} while (0);

	return false;
}


GameSprite* GameBattleLayer::createSprite( int32t nSN,
									 ESpriteCamp eCamp,
									 ESpriteDir eDir, 
									 float activeTime )
{
	GameScene* pScene = GAMESCENE;

	GameSprite* pSprite = GameSprite::create(nSN);
	GAME_ASSERT_RET(pSprite, NULL, ( "invalid data"));
	TAimMoveType eMoveType = pSprite->getMoveType();
	pSprite->setStatus(ESS_Standing);	//站立姿态
	pSprite->setDir(eDir);
	pSprite->setCamp(eCamp);
	pSprite->setPosition(eCamp == ESC_Player ? pScene->getSpritePlayerBronPoint(eMoveType) : pScene->getSpriteAIBronPoint(eMoveType));
	pSprite->schedule(schedule_selector(GameSprite::doActivate), activeTime);
	pSprite->setVisible(false);
	return pSprite;
}

void GameBattleLayer::onSpriteDead( GameSprite* sprite )
{
	GAME_ASSERT_RET(sprite, ;, ( "why??"))

	ESpriteCamp eCamp = sprite->getCamp();
	GameWorld* pGameWorld = GAMEWORLD;

	GameCamp* pCamp = pGameWorld->getCamp(eCamp);
	GAME_ASSERT_RET(pCamp, ;, ( "oh...??"));

	int nSN = sprite->getSN();

	if (eCamp == ESC_AI)
	{
		giveDrop(nSN);	//掉落计算
		m_aEnemies->removeObject(sprite);
	}
	else
	{
		m_aArms->removeObject(sprite);
	}

	bool bIsHero = sprite->isHero();

	removeChild(sprite);

	if (pCamp->getCoreArm() == nSN || bIsHero)
	{
		onCompleteScene(eCamp, nSN);	//结算
	}
}

void GameBattleLayer::onCompleteScene(ESpriteCamp eCamp, int nSpriteSN)
{
	int nCurrentSceneSN = GAMESCENE->getSN();
	const TemplateScene* pSceneTemp = GAMEWORLD->get<TemplateScene>(nCurrentSceneSN);
	GAME_ASSERT_RET(pSceneTemp, ;, ( "scene not found!!"));
	string strLua = pSceneTemp->getCompleteluafunc();

	CSJson::Value ret = LUAHELPER->executeGlobalFunction(strLua.c_str(), 0)["val"];

	int nMoney = ret["money"].asInt();
	int res = ret["res"].asInt();

	CCDirector::sharedDirector()->replaceScene(CCTransitionSplitCols::create(1, GameResultScene::create(eCamp)));
}


void GameBattleLayer::changeResNum( int32t nRes )
{
	m_nRes += nRes;
	if (m_nRes < 0)
	{
		m_nRes = 0;
	}
	
	UIBATTLELAYER->upateRes(m_nRes);
}

void GameBattleLayer::changeMoneyNum( int32t nMoeny )
{
	//处理UI相关逻辑？
	m_pHero->incMoney(nMoeny);
}

void GameBattleLayer::changeEneryNum( int32t nEnery )
{
	//处理UI相关逻辑？
	m_pHero->incEnery(nEnery);
}

void GameBattleLayer::incRes( float dt )
{
	changeResNum(GAMEWORLD->getIncRes());
}

void GameBattleLayer::menuArmCallback( CCObject* pSender )
{
	UIButton* pBtn = (UIButton*)pSender;
	string str = pBtn->getName();
	if (str == "arm1")
	{
		playerAddSprite(10000);
	}
	else
	{
		playerAddSprite(10001);
	}
}

void GameBattleLayer::menuBuildingCallback( CCObject* pSender )
{
	UIButton* pBtn = (UIButton*)pSender;
}

vector<GameSprite*> GameBattleLayer::onSkillEffect( GameSprite* pSprite, GameSkill* pSkill )
{
	vector<GameSprite*> vtRet;

	GAME_ASSERT_RET(pSkill, vtRet, ( "invalid skill??"));
	GAME_ASSERT_RET(pSprite, vtRet, ( "invalid pSprite??"));

	const TemplateSkill* pSkillTemplate = pSkill->GetTemplate();
	ESpriteCamp eCamp = pSprite->getCamp();
	CCArray* pArry = eCamp == ESC_AI ? m_aArms : m_aEnemies;

	TAOEType eAoeType = pSkillTemplate->getAoetype();

	CCObject* pObj = NULL;
	CCPoint pos = pSkill->getSkillSpritePostion();
	ESpriteDir eDir = pSprite->getDir();
	switch (eAoeType)
	{
	case TAOEType_line:
		{
			const AOELine& lineSetting = pSkillTemplate->getLinesetting();

			CCRect rect(pos.x, pos.y, lineSetting.width, lineSetting.height);

			if (eDir == ESD_Right)
			{
				rect.origin.x -= lineSetting.width;
			}

			CCARRAY_FOREACH(pArry, pObj)
			{
				GameSprite* pEnemy = (GameSprite*)pObj;
				if (pEnemy->isDead())	//已经挂了的 不处理
				{
					continue;
				}

				if (rect.containsPoint(pEnemy->getSpritePosition()))
				{
					vtRet.push_back(pEnemy);
				}

			}
		}
		break;
	case TAOEType_sector:
		{
			const AOESector& sectorSetting = pSkillTemplate->getSectorsetting();
			CCARRAY_FOREACH(pArry, pObj){
				GameSprite* pEnemy = (GameSprite*)pObj;
				if (pEnemy->isDead())	//已经挂了的 不处理
				{
					continue;
				}

				if (eDir == ESD_Left)
				{
					if (MathTools::IsPointInCircularSector(pos, sectorSetting.Radio, sectorSetting.MinAngle + 180, sectorSetting.MaxAngle + 180, pEnemy->getSpritePosition()))
					{
						vtRet.push_back(pEnemy);
					}
				}
				else
				{
					if (MathTools::IsPointInCircularSector(pos, sectorSetting.Radio, sectorSetting.MinAngle, sectorSetting.MaxAngle, pEnemy->getSpritePosition()))
					{
						vtRet.push_back(pEnemy);
					}
				}

			}
		}
		break;
	default:
		GAME_ASSERT_RET(false, vtRet, ( "invalid aoe type"));
		break;
	}

	//计算具体伤害值
	for (uint32t i = 0; i < vtRet.size(); ++i)
	{
		GameSprite* pTmpSprite = vtRet.at(i);
		pTmpSprite->retain();	//等到击中特效播放完成 relase。
		int nAimSN = pTmpSprite->getSN();
		pTmpSprite->onHurt(pSkill->calHurtPoint(nAimSN, pSprite->getSN()));
	}

	return vtRet;
}

void GameBattleLayer::giveDrop( int32t nArmSN )
{
	const TemplateArms* pArm = GAMEWORLD->get<TemplateArms>(nArmSN);
	GAME_ASSERT_RET(pArm, ;, ( "invalid arm sn"));
	const vector<SDropGroupItem>& vtDropGroup = pArm->getDropgroup();

	for (uint32t i = 0; i < vtDropGroup.size(); ++i)
	{
		const SDropGroupItem& stDropItem = vtDropGroup.at(i);
		if (stDropItem.rate < 1)	
		{	
			int nRate = stDropItem.rate * 1000;
			if (nRate < rand() % 1000)
			{
				continue;//概率不满足？？
			}
		}

		switch (stDropItem.dropType)
		{
		case TDropType_res: //资源
			{
				changeResNum(stDropItem.num);
				break;
			}
		case TDropType_energy: //能量
			{
				changeEneryNum(stDropItem.num);
				break;
			}
		case  TDropType_moeny: //金钱
			{
				changeMoneyNum(stDropItem.num);
				break;;
			}
		default:
			continue;
		}
	}

}

