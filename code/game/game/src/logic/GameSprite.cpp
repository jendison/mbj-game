#include "GameSprite.h"
#include <algorithm>
#include <sprite_nodes/CCSprite.h>
#include <sprite_nodes/CCSpriteBatchNode.h>
#include "GameAnimation.h"
#include <actions/CCActionInterval.h>
#include <actions/CCActionInstant.h>
#include <cocoa/CCObject.h>
#include <cocoa/CCGeometry.h>
#include <draw_nodes/CCDrawingPrimitives.h>
#include "TypeDefine.h"
#include "../template/TemplateArms.h"
#include "GameWorld.h"

#include "../template/TemplateAi.h"
#include "GameScene.h"
#include "Macro.h"
#include "GameBattleLayer.h"

using namespace cocos2d;



const char* g_strSpriteAnimationDir[ESS_Cnt] = 
{
	"walk",
	"attack",
	"walk",
	"dead",
	"attacked"
};


GameSprite::GameSprite():CCNode(), m_eStatus(ESS_Standing)
{
	m_pGameAnimation = NULL;
	m_nMaxHP = 0;
	m_nHP =  0 ;		//
	m_nCD = 0;		//
	m_fSpeed = 0;	//	
	m_nCostNum =	0;	//消耗资源的数量
	m_eCamp = ESC_AI;	//所属阵营
	m_bIsActive = false;
	m_nSN = 0;
	m_fBirthTime = 0;
	m_bIsInCastSkillStatus = false;
	m_eMoveType = TAimMoveType_Cnt;

#if _DEBUG
	 m_pCurrentSkill = NULL;
#endif
}

GameSprite::~GameSprite()
{
#ifdef _DEBUG
	CCLOG("%d release", m_nSN);
#endif // _DEBUG

	for (vector<GameSkill*>::iterator itr = m_pSkillList.begin(); itr != m_pSkillList.end(); ++itr)
	{
		(*itr)->release();
	}
}


void GameSprite::onExit()
{
	unscheduleUpdate();
	unscheduleAllSelectors();
	m_bIsActive = false;

	for (vector<GameSkill*>::iterator itr = m_pSkillList.begin(); itr != m_pSkillList.end(); ++itr)
	{
		(*itr)->onExit();
	}

	m_pGameAnimation->getAnimation()->stop();
	removeChild(m_pGameAnimation);
}


bool GameSprite::initWithGame(int32t nSN)
{
	GameWorld* pGameWorld = GAMEWORLD;

	const TemplateArms* pArm = pGameWorld->get<TemplateArms>(nSN);
	GAME_ASSERT_RET(pArm, false, ( "invalid templte of scene"));
	m_strSpriteFilePath = pArm->getAnimatepath();
	m_nSN = nSN;
	bool bRet = false;
	do 
	{
		m_pGameAnimation = GameAnimtion::create(CCString::createWithFormat("%s", pArm->getAnimatepath().c_str())->getCString());
		GAME_ASSERT_RET(m_pGameAnimation, false, ( "init animate fail"));
		addChild(m_pGameAnimation);

		m_nMaxHP = pArm->getHp();
		m_nHP =  m_nMaxHP ;		//
		m_nCD = pArm->getCd();		//
		m_fSpeed = pArm->getSpeed();	//	
		m_nCostNum =	pArm->getCostnum();	//消耗资源的数量
		m_eCamp = ESC_AI;	//所属阵营
		m_eMoveType = pArm->getMovetype();
		setAnchorPoint(ccp(0.5, 0));

		//初始化技能
		const vector<int32t>& skillList = pArm->getActiveskill();
		for (vector<int32t>::const_iterator itr = skillList.begin(); itr != skillList.end(); ++itr)
		{
			GameSkill* pSkill = GameSkill::create(*itr);
			if (pSkill)
			{
				pSkill->retain();
				m_pSkillList.push_back(pSkill);
			}
		}

		scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;
}

GameSprite* GameSprite::create( int32t nSN)
{
	GameSprite* pSprite = new GameSprite();
	if (pSprite && pSprite->initWithGame(nSN))
	{
		pSprite->autorelease();
		return pSprite;
	}
	
	delete pSprite;
	pSprite = NULL;
	return NULL;
}

bool GameSprite::setStatus( ESpriteStatus eStatus, cocos2d::CCCallFuncND* onStatusEnd)
{
	GAME_ASSERT_RET(eStatus < ESS_Cnt, false, ("out of bound"));

	if (ESS_Dying == m_eStatus)
	{
		return false;
	}

	if (ESS_Attacked == eStatus)
	{
		////播放动画
		//CCActionInterval*  action2 = CCTintBy::create(0.1, 0, -255, -255);
		//CCActionInterval*  reverse = action2->reverse();
		//m_pGameAnimation->runAction( CCSequence::create(action2, reverse, NULL));
		m_eStatus = eStatus;
		return true;
	}
	
	bool bLoop = false;
	if (eStatus == ESS_Runnig || eStatus == ESS_Standing)
	{
		bLoop = true;
	}

	m_pGameAnimation->play(g_strSpriteAnimationDir[eStatus], onStatusEnd, bLoop);

	m_eStatus = eStatus;
	return true;
}

bool GameSprite::moveto( const cocos2d::CCPoint& postion, float fSpeed,  CCCallFuncND*  onMoveDone)
{
	//if (m_eStatus == ESS_Runnig)
	//{
	//	return false;
	//}

	float fDis = ccpLength(postion);
	CCActionInterval*  a1 = CCMoveBy::create(fDis / fSpeed, postion);

	runAction(CCSequence::create(a1, onMoveDone, NULL));
	setStatus(ESS_Runnig);

	return true;
}

bool GameSprite::fightWith( GameSprite* pAim, cocos2d::CCCallFuncND* onFightDone )
{
	CCActionInterval* a1 = CCDelayTime::create(1);
	runAction(CCSequence::create(a1, onFightDone, NULL));
	return setStatus(ESS_Attacking);
}


bool GameSprite::setDir( ESpriteDir eDir )
{
	if (eDir == m_eDir)
	{
		return true;
	}

	if (eDir == ESD_Right)
	{
		m_pGameAnimation->setScaleX(-1);
	}
	else
	{
		m_pGameAnimation->setScaleX(1);
	}

	m_eDir = eDir;

	return true;
}

void GameSprite::onHurt( int nPoint )
{
	if (isDead())
	{
		return;
	}

	CCActionInterval*  action2 = CCTintBy::create(0.2, 0, 10, 10);
	CCActionInterval*  reverse = action2->reverse();
	m_pGameAnimation->runAction( CCSequence::create(action2, reverse, NULL));

	m_nHP -= nPoint;
	if (m_nHP <= 0)
	{
		m_nHP = 0;
		setStatus(ESS_Dying, CCCallFuncND::create(this, callfuncND_selector(GameSprite::doDead), NULL));
	}
}

bool GameSprite::isDead()
{
	return m_nHP == 0;
}

void GameSprite::drawHealthBar()
{
	static int nWidth = 20;	//宽度一半
	static int nHeight = 1;//高度一半
	cocos2d::CCPoint pos = ccp(0,0);

	CCRect rect = m_pGameAnimation->boundingBox();

	pos.y += rect.size.height * 0.5;

	float x_l = pos.x - nWidth ;
	float x_r = pos.x + nWidth;
	float y_t = pos.y + nHeight + 10;
	float y_b = pos.y - nHeight + 10;

	CCPoint healthBarBack[] = {
		ccp(x_l, y_t),
		ccp(x_r, y_t),
		ccp(x_r, y_b),
		ccp(x_l, y_b)
	};
	ccDrawSolidPoly(healthBarBack, 4, ccc4f(255, 0, 0, 255));

	int n = (float)(m_nHP * nWidth * 2)/ m_nMaxHP;
	CCPoint healthBar[] = {
		ccp(x_l,y_t),
		ccp(x_l + n , y_t),
		ccp(x_l + n, y_b),
		ccp(x_l, y_b)
	};
	ccDrawSolidPoly(healthBar, 4, ccc4f(0, 255, 0, 255));
}

void GameSprite::draw()
{
	CCNode::draw();
	drawHealthBar();

#ifdef _DEBUG
	if (m_pCurrentSkill == NULL)
	{
		return;
	}

	CCPoint myPostition = getPosition();
	const TemplateSkill* pSkillTemp = m_pCurrentSkill->GetTemplate();

	TAOEType eAOEType = pSkillTemp->getAoetype();
	if (eAOEType == TAOEType_line)
	{
		CCPoint point = m_pCurrentSkill->getSkillSpritePostion() - myPostition;
		const AOELine& line = pSkillTemp->getLinesetting();
		CCPoint point1 = point;
		point1.x += line.width;
		CCPoint point2 = point1;
		point2.y += line.height;
		CCPoint point3 = point;
		point3.y += line.height;

		//线
		glLineWidth( 5.0f ); //线宽
		ccDrawColor4B(255,0,0,255);//画笔颜色
		ccDrawLine( point, point1);//画一条线
		ccDrawLine( point1, point2);//画一条线
		ccDrawLine( point2, point3);//画一条线
		ccDrawLine( point3, point);//画一条线
	}
	else if (eAOEType == TAOEType_sector)
	{
		CCPoint point = m_pCurrentSkill->getSkillSpritePostion() - myPostition;
		const AOESector& sec = pSkillTemp->getSectorsetting();
		glLineWidth( 5.0f ); //线宽
		ccDrawColor4B(255,0,0,255);//画笔颜色
		//ccDrawCircle(point, sec.Radio, 60, 360, false);
		if (m_eDir == ESD_Left)
		{
			ccDrawSolidCircle(point, sec.Radio, sec.MinAngle + 180, sec.MaxAngle - sec.MinAngle, 180, 1, 1);
		}
		else
		{
			ccDrawSolidCircle(point, sec.Radio, sec.MinAngle, sec.MaxAngle - sec.MinAngle, 180, 1, 1);
		}
	}

#endif // _DEBUG
}

void GameSprite::doActivate( float dt )
{
	//m_pGame->spriteMoveWithDir(this);
	m_bIsActive = true;
	setVisible(true);
	setStatus(ESS_Runnig);
	unschedule(schedule_selector(GameSprite::doActivate));
}

void GameSprite::update( float delta )
{
	if (!m_bIsActive || m_eStatus == ESS_Dying)
	{
		return;
	}

	m_fBirthTime += delta;
	updateSkill(delta);

	//刷新技能技能
	do 
	{
		//精灵每帧处理流程
		//	1.自动攻击敌对目标
		//		1）选择技能
		//			所有cd结束的技能按权重比例随机选取。	

		if (isHero() && isCanRun())
		{
			break;
		}
			//当前技能
		if (m_bIsInCastSkillStatus)	//前摇时间内 不计算技能
		{
			return;
		}

		GameSkill* pCurrentSkill = selectASkill();
		CC_BREAK_IF(!pCurrentSkill);

		if (pCurrentSkill->isInCD())	//技能正在CD中。
		{
			return;
		}

		//		2）根据技能选中一个或多个目标
		GameSprite* pAim = selectAim(pCurrentSkill);
		CC_BREAK_IF(!pAim);

#ifdef _DEBUG
		CCLOG("%d select aim %d", m_nSN, pAim->getSN());
#endif // _DEBUG

		if (ESS_Attacking != m_eStatus)
		{

#ifdef _DEBUG
			CCLOG("%d attack %d", m_nSN, pAim->getSN());
			m_pCurrentSkill = pCurrentSkill;
#endif // _DEBUG

			pAim->retain();	//防止死亡之后 野指针， 回调时释放

			pCurrentSkill->resetCD();

			//		3）自己播放攻击准备动画
			setStatus(ESS_Attacking, CCCallFuncND::create(this, callfuncND_selector(GameSprite::callback_AttackEnd), pCurrentSkill));

			CREATE_CALLBACK_ARG_2(pCurrentSkill, pAim);
			CCSequence* pAction = CCSequence::create(CCDelayTime::create(pCurrentSkill->getStartPlaySkillEffectTime() / 1000.0f), 
				CCCallFuncND::create(this, callfuncND_selector(GameSprite::callback_palySkillEffect), pArg), NULL);

			runAction(pAction);

			//前摇阶段
			m_bIsInCastSkillStatus = true;
		}

		return;
	} while (0);

	//1.自动攻击敌对目标
	//m_pGame->onSpriteMove(this);

	if (!isCanRun())
	{
		return;
	}

	//	2.移动
	if (m_eStatus == ESS_Standing)
	{
		setStatus(ESS_Runnig);
	}

	if (m_eStatus == ESS_Runnig)
	{

		float x = getPositionX();
		float dlt = m_fSpeed * delta * (m_eDir == ESD_Right ? 1 : -1);
		GameScene* pScene = GAMESCENE;
		CCSize mapSize =	pScene ->getMapSize();
		CCSize tileSize =	pScene->getTileSize();
		float mapLength = mapSize.width * tileSize.width;

		x += dlt;
		if (x < 0)
		{
			x = 0;
		}
		else if (x > mapLength)
		{
			x = mapLength;
		}

		setPositionX(x);		
	}
}

void GameSprite::doDead(cocos2d::CCNode* pNode, void* p)
{
#ifdef _DEBUG
	CCLOG("%d dead", m_nSN);
#endif // _DEBUG

	//onExit();
	BATTLELAYER->onSpriteDead(this);
}

GameSkill* GameSprite::selectASkill()
{
	if (m_pSkillList.empty())
	{
		return NULL;
	}

	const TemplateArms* pArm = GAMEWORLD->get<TemplateArms>(m_nSN);
	GAME_ASSERT_RET(pArm, NULL, ( "get arm by sn fail"));

	int nAISN = pArm->getAiconfig();		//AISN可能为0

	const TemplateAi* pAI = NULL;
	if (nAISN != 0)
	{
		pAI = GAMEWORLD->get<TemplateAi>(nAISN);
	}

	//AI数据错误？
	if (pAI == NULL)	
	{
		return m_pSkillList.at(0);
	}
	
	//针对AI选项依次判断
	const vector<SAIConfig>& vtAIConfig = pAI->getAiconfig();

	for (uint32t i = 0; i < vtAIConfig.size(); ++i)
	{
		const SAIConfig& ai = vtAIConfig.at(i);
		GameSkill* pSkill = getSkill(ai.skill);
		if (pSkill && !pSkill->isInCD())
		{
			if (ai.type == TAIOpenType_afterBirthTime)
			{
				if (ai.number < m_fBirthTime * 1000)
				{
					pSkill->setCD(GAMEMAX(pSkill->getCD(), ai.loopTime));	//设置CD
					return pSkill;
				}
			}
			else if (ai.type == TAIOpenType_HPPecent)
			{
				if ((ai.number / 100.0f) > (m_nHP * 1.0f / m_nMaxHP))
				{
					pSkill->setCD(GAMEMAX(pSkill->getCD(), ai.loopTime));//设置CD
					return pSkill;
				}
			}
		}
	}

	return m_pSkillList.at(0);	//第一个技能默认是普通攻击
}


GameSprite*  GameSprite::selectAim( GameSkill* pSkill )
{
	return BATTLELAYER->selectAim(this, pSkill);
}


void GameSprite::callback_AttackEnd( cocos2d::CCNode* pNode, void*p )
{
	if (m_eStatus != ESS_Dying)
	{
		setStatus(ESS_Standing);	//攻击动作播放结束。
	}
}

void GameSprite::callback_skillEffectCastPlayOver(cocos2d::CCNode* pNode, void* p)
{
	//		5）同时计算结果和播放对方被击中特效
	GameSkill* pSkill = (GameSkill*)p;

}

void GameSprite::updateSkill(float dt)
{
	for (uint32t i = 0; i < m_pSkillList.size(); ++i)
	{
		GameSkill* pSkill = m_pSkillList[i];
		pSkill->update(dt);
	}
}

void GameSprite::callback_skillEffectHitPlayOver( cocos2d::CCNode* pNode, void* p)
{

}

void GameSprite::callback_palySkillEffect(cocos2d::CCNode* pNode, void* p)
{
	m_bIsInCastSkillStatus = false;

	CallBackArg* ptr = (CallBackArg*)p;	//还有用，不用释放

	GameSkill* pSkill = (GameSkill*)ptr->args[0];
	GameSprite* pAim = (GameSprite*)ptr->args[1];

	if (pAim->isDead())
	{
		CC_SAFE_RELEASE(pAim);	//update 里的retain
		CC_SAFE_DELETE(p);
		CCLOG("aim sprite dead no play Trajectory effect");
		return;
	}

	GAME_ASSERT_RET(pSkill, ;, ( "must have skill"));

	pSkill->playSoundEffect(TSkillEffectType_cast);
	pSkill->resetCD();

	if (pSkill->isTrajectory())	//有弹道
	{
		//计算弹道移动
		CCPoint myPoint = getPosition();
		float fSpeed = pSkill->getTrajectorySpeed();

		pSkill->playEffect_trajectory(CCCallFuncND::create(this, callfuncND_selector(GameSprite::callback_skillEffectTrajectoryPlayOver), p),
			myPoint, pAim, fSpeed );
	}
	else
	{
		callback_skillEffectTrajectoryPlayOver(NULL, p);
	}
}

void GameSprite::callback_skillEffectTrajectoryPlayOver( cocos2d::CCNode* pNode, void* p )
{
	CallBackArgPointer ptr((CallBackArg*)p);	//没有用了，自动释放

	GameSkill* pSkill = (GameSkill*)ptr->args[0];
	GameSprite* pAim = (GameSprite*)ptr->args[1];

	if (pAim->isDead())	//目标已死？
	{
		CCLOG("aim sprite dead no play aoe effect");
		CC_SAFE_RELEASE(pAim);	//和update里的配对
		return;
	}

	//弹道结束之后。
	GAME_ASSERT_RET(pSkill, ;, ( "must have skill"));

	CCPoint pos = getPosition();	//无弹道 以自己为中心的aoe技能
	if (pSkill->isTrajectory())	//有弹道，以目标为aoe的技能
	{
		pos = pAim->getSpritePosition();
	}

	//播放施展AOE技能
	pSkill->playEffect_cast(CCCallFuncND::create(this, callfuncND_selector(GameSprite::callback_skillEffectCastPlayOver), pSkill), pos);
	CC_SAFE_RELEASE(pAim);	//和update里的配对

	vector<GameSprite*> vtRet = BATTLELAYER->onSkillEffect(this, pSkill);

	//击中特效， 可能需要复制几分
	pSkill->playEffect_hit(this, vtRet);

	//对方受到攻击
	for (int i = 0; i < vtRet.size(); ++i)
	{
		GameSprite* pSprite = vtRet.at(i);
		pSprite->setStatus(ESS_Attacked);
	}
}

GameSkill* GameSprite::getSkill( int32t nSkill )
{
	for (uint32t i = 0; i < m_pSkillList.size(); ++i)
	{
		GameSkill* pSkill = m_pSkillList.at(i);
		if (pSkill && pSkill->getSN() == nSkill)
		{
			return pSkill;
		}
	}

	return NULL;
}
