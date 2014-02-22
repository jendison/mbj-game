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
	m_nCostNum =	0;	//������Դ������
	m_eCamp = ESC_AI;	//������Ӫ
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
		m_nCostNum =	pArm->getCostnum();	//������Դ������
		m_eCamp = ESC_AI;	//������Ӫ
		m_eMoveType = pArm->getMovetype();
		setAnchorPoint(ccp(0.5, 0));

		//��ʼ������
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
		////���Ŷ���
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
	static int nWidth = 20;	//���һ��
	static int nHeight = 1;//�߶�һ��
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

		//��
		glLineWidth( 5.0f ); //�߿�
		ccDrawColor4B(255,0,0,255);//������ɫ
		ccDrawLine( point, point1);//��һ����
		ccDrawLine( point1, point2);//��һ����
		ccDrawLine( point2, point3);//��һ����
		ccDrawLine( point3, point);//��һ����
	}
	else if (eAOEType == TAOEType_sector)
	{
		CCPoint point = m_pCurrentSkill->getSkillSpritePostion() - myPostition;
		const AOESector& sec = pSkillTemp->getSectorsetting();
		glLineWidth( 5.0f ); //�߿�
		ccDrawColor4B(255,0,0,255);//������ɫ
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

	//ˢ�¼��ܼ���
	do 
	{
		//����ÿ֡��������
		//	1.�Զ������ж�Ŀ��
		//		1��ѡ����
		//			����cd�����ļ��ܰ�Ȩ�ر������ѡȡ��	

		if (isHero() && isCanRun())
		{
			break;
		}
			//��ǰ����
		if (m_bIsInCastSkillStatus)	//ǰҡʱ���� �����㼼��
		{
			return;
		}

		GameSkill* pCurrentSkill = selectASkill();
		CC_BREAK_IF(!pCurrentSkill);

		if (pCurrentSkill->isInCD())	//��������CD�С�
		{
			return;
		}

		//		2�����ݼ���ѡ��һ������Ŀ��
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

			pAim->retain();	//��ֹ����֮�� Ұָ�룬 �ص�ʱ�ͷ�

			pCurrentSkill->resetCD();

			//		3���Լ����Ź���׼������
			setStatus(ESS_Attacking, CCCallFuncND::create(this, callfuncND_selector(GameSprite::callback_AttackEnd), pCurrentSkill));

			CREATE_CALLBACK_ARG_2(pCurrentSkill, pAim);
			CCSequence* pAction = CCSequence::create(CCDelayTime::create(pCurrentSkill->getStartPlaySkillEffectTime() / 1000.0f), 
				CCCallFuncND::create(this, callfuncND_selector(GameSprite::callback_palySkillEffect), pArg), NULL);

			runAction(pAction);

			//ǰҡ�׶�
			m_bIsInCastSkillStatus = true;
		}

		return;
	} while (0);

	//1.�Զ������ж�Ŀ��
	//m_pGame->onSpriteMove(this);

	if (!isCanRun())
	{
		return;
	}

	//	2.�ƶ�
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

	int nAISN = pArm->getAiconfig();		//AISN����Ϊ0

	const TemplateAi* pAI = NULL;
	if (nAISN != 0)
	{
		pAI = GAMEWORLD->get<TemplateAi>(nAISN);
	}

	//AI���ݴ���
	if (pAI == NULL)	
	{
		return m_pSkillList.at(0);
	}
	
	//���AIѡ�������ж�
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
					pSkill->setCD(GAMEMAX(pSkill->getCD(), ai.loopTime));	//����CD
					return pSkill;
				}
			}
			else if (ai.type == TAIOpenType_HPPecent)
			{
				if ((ai.number / 100.0f) > (m_nHP * 1.0f / m_nMaxHP))
				{
					pSkill->setCD(GAMEMAX(pSkill->getCD(), ai.loopTime));//����CD
					return pSkill;
				}
			}
		}
	}

	return m_pSkillList.at(0);	//��һ������Ĭ������ͨ����
}


GameSprite*  GameSprite::selectAim( GameSkill* pSkill )
{
	return BATTLELAYER->selectAim(this, pSkill);
}


void GameSprite::callback_AttackEnd( cocos2d::CCNode* pNode, void*p )
{
	if (m_eStatus != ESS_Dying)
	{
		setStatus(ESS_Standing);	//�����������Ž�����
	}
}

void GameSprite::callback_skillEffectCastPlayOver(cocos2d::CCNode* pNode, void* p)
{
	//		5��ͬʱ�������Ͳ��ŶԷ���������Ч
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

	CallBackArg* ptr = (CallBackArg*)p;	//�����ã������ͷ�

	GameSkill* pSkill = (GameSkill*)ptr->args[0];
	GameSprite* pAim = (GameSprite*)ptr->args[1];

	if (pAim->isDead())
	{
		CC_SAFE_RELEASE(pAim);	//update ���retain
		CC_SAFE_DELETE(p);
		CCLOG("aim sprite dead no play Trajectory effect");
		return;
	}

	GAME_ASSERT_RET(pSkill, ;, ( "must have skill"));

	pSkill->playSoundEffect(TSkillEffectType_cast);
	pSkill->resetCD();

	if (pSkill->isTrajectory())	//�е���
	{
		//���㵯���ƶ�
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
	CallBackArgPointer ptr((CallBackArg*)p);	//û�����ˣ��Զ��ͷ�

	GameSkill* pSkill = (GameSkill*)ptr->args[0];
	GameSprite* pAim = (GameSprite*)ptr->args[1];

	if (pAim->isDead())	//Ŀ��������
	{
		CCLOG("aim sprite dead no play aoe effect");
		CC_SAFE_RELEASE(pAim);	//��update������
		return;
	}

	//��������֮��
	GAME_ASSERT_RET(pSkill, ;, ( "must have skill"));

	CCPoint pos = getPosition();	//�޵��� ���Լ�Ϊ���ĵ�aoe����
	if (pSkill->isTrajectory())	//�е�������Ŀ��Ϊaoe�ļ���
	{
		pos = pAim->getSpritePosition();
	}

	//����ʩչAOE����
	pSkill->playEffect_cast(CCCallFuncND::create(this, callfuncND_selector(GameSprite::callback_skillEffectCastPlayOver), pSkill), pos);
	CC_SAFE_RELEASE(pAim);	//��update������

	vector<GameSprite*> vtRet = BATTLELAYER->onSkillEffect(this, pSkill);

	//������Ч�� ������Ҫ���Ƽ���
	pSkill->playEffect_hit(this, vtRet);

	//�Է��ܵ�����
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
