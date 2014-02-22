#include "GameSkill.h"
#include <cocos2d.h>
#include "GameWorld.h"
#include "Macro.h"
#include "../template/TemplateSkill.h"
#include "GameAnimation.h"
#include "sprite_nodes/CCSprite.h"
#include "GameBattleLayer.h"
#include "GameScene.h"
#include "LuaHelper.h"

using namespace cocos2d;

GameSkill::GameSkill()
{
	m_nPoint = rand() % 50 + 1;		//伤害点数
	m_nSN = 0;
	m_nCD = 0;
	m_nCDTimer = 0;
}

GameSkill::~GameSkill()
{
	stopAllAction();
}

GameSkill* GameSkill::create( int32t nSN)
{
	GameSkill* pSkill = new GameSkill();

	if (pSkill && pSkill->initWithGame(nSN))
	{
		pSkill->autorelease();
		return pSkill;
	}

	delete pSkill;
	pSkill = NULL;
	return NULL;
}

bool GameSkill::initWithGame( int32t nSN )
{
	GameWorld* pGameWorld = GAMEWORLD;

	const TemplateSkill* pSkillTemplate =  pGameWorld->get<TemplateSkill>(nSN);
	GAME_ASSERT_RET(pSkillTemplate, false, ("invalid dataforget replace data?"));

	do 
	{		
		m_nCD = pSkillTemplate->getSkillcd();
		m_nCDTimer = m_nCD;
		
		const vector<SkillEffect>& vtSkillEffect = pSkillTemplate->getEffectres();
		for (uint32t i = 0; i < vtSkillEffect.size(); ++i)
		{
			const SkillEffect& se = vtSkillEffect[i];
			if (se.skillEffectPath.empty())
			{
				continue;
			}

			m_aSoundEffect[se.skillEffectType] = se.skillSoundPath;
			m_aAnimationsEffect[se.skillEffectType] = se.skillEffectPath;
		}

		m_nSN = nSN;
	} while (0);
	return true;
}

void GameSkill::playEffect_cast( cocos2d::CCCallFuncND* pCallBack, const CCPoint& pos )
{
	m_curPos = pos;
	GameAnimtion* pAnimation = GameAnimtion::create(m_aAnimationsEffect[TSkillEffectType_cast].c_str());
	if (pAnimation)
	{
		BATTLELAYER->addChild(pAnimation);

		pAnimation->setPosition(pos);
		if (pCallBack)
		{
			pCallBack->retain();
		}
		pAnimation->play(0, CCCallFuncND::create(this, callfuncND_selector(GameSkill::callback_playEffect_cast), pCallBack));
	}
}

void GameSkill::callback_playEffect_cast( cocos2d::CCNode* pNode, void* p )
{
	CCCallFuncND* pCallBack = (CCCallFuncND*)p;
	if (pCallBack)
	{
		pCallBack->startWithTarget(pNode);
		pCallBack->execute();
		pCallBack->release();
	}

	BATTLELAYER->removeChild(pNode);
}

void GameSkill::stopAllAction()
{
	for (std::list<SkillEffectPostionInfo>::iterator itr = m_skillEffectPostionInfo.begin(); itr != m_skillEffectPostionInfo.end(); ++itr)
	{
		SkillEffectPostionInfo& info = *itr;

		if (info.eType == ESEF_Moveto)
		{
			info.pCallBack->startWithTarget(info.pMe);
			info.pCallBack->execute();
			info.pCallBack->release();

			info.pMe->removeFromParent();
			info.pMe->release();
		}
	}
	m_skillEffectPostionInfo.clear();
}



void GameSkill::playEffect_trajectory(cocos2d::CCCallFuncND* pCallBack, const cocos2d::CCPoint& srcPoint, GameSprite* pAimSprite, float fSpeed)
{
	playSoundEffect(TSkillEffectType_trajectory);

	GameAnimtion* pAnimation = GameAnimtion::create(m_aAnimationsEffect[TSkillEffectType_trajectory].c_str());
	if (pAnimation)
	{
		BATTLELAYER->addChild(pAnimation);
		pAnimation->setPosition(srcPoint);

		SkillEffectPostionInfo info(ESEF_Moveto);
		pCallBack->retain();	//必须retain一下

		//更新位置
		info.pAim = pAimSprite;
		info.pCallBack = pCallBack;
		info.pMe = pAnimation;
		m_skillEffectPostionInfo.push_back(info);
		pAnimation->retain();

		//循环播放动画
		pAnimation->play(0, NULL, 1);
	}
}

void GameSkill::playEffect_hit(GameSprite* pSelf, const vector<GameSprite*>&  aimSprite)
{
	playSoundEffect(TSkillEffectType_hit);

	for (uint32t i = 0; i < aimSprite.size(); ++i)
	{	
		GameAnimtion* pAnimation = GameAnimtion::create(m_aAnimationsEffect[TSkillEffectType_hit].c_str());
		if (pAnimation)
		{
			BATTLELAYER->addChild(pAnimation);
			const CCPoint& point = aimSprite.at(i)->getSpritePosition();
			pAnimation->setPosition(point);
			pAnimation->setPositionY(pAnimation->getPositionY());
			GameSprite* pAim = aimSprite.at(i);

			//位置跟随
			SkillEffectPostionInfo info(ESEF_Follow);
			info.pAim = pAim;
			info.pMe = pAnimation;
			m_skillEffectPostionInfo.push_back(info);
			pAim->release();
			
			//回调的时候删除自己
			CCCallFuncND* pCallBack = CCCallFuncND::create(pSelf, callfuncND_selector(GameSprite::callback_skillEffectHitPlayOver), aimSprite.at(i));
			pCallBack->retain();
			pAnimation->play(0, CCCallFuncND::create(this, callfuncND_selector(GameSkill::callback_playEffect_hit), pCallBack));
		}
	}
}

void GameSkill::callback_playEffect_hit( cocos2d::CCNode* pNode, void* p )
{
	CCCallFuncND* pCallBack = (CCCallFuncND*)p;
	if (pCallBack)
	{
		pCallBack->startWithTarget(pNode);
		pCallBack->execute();
		pCallBack->release();
	}

	removeFromSkillEffectPostionInfo(pNode);
	BATTLELAYER->removeChild(pNode);
}


void GameSkill::update( float dt )
{
	m_nCDTimer += (dt * 1000);	//外面的单位是秒

	for (std::list<SkillEffectPostionInfo>::iterator itr = m_skillEffectPostionInfo.begin(); itr != m_skillEffectPostionInfo.end(); )
	{
		SkillEffectPostionInfo& info = *itr;
		if (info.eType == ESEF_Moveto)	//控制位置， 控制回调
		{
			CCPoint ptMe = info.pMe->getPosition();
			CCPoint ptAim = info.pAim->getPosition();
			float fSpeed = GetTemplate()->getTrajectoryspeed();

			float fDistance = ccpDistance(ptMe, ptAim);
			float t = fDistance / fSpeed;
	
			float xSpeed = fabsf(ptMe.x - ptAim.x) / t;
			float ySpeed = fabsf(ptMe.y - ptAim.y) / t;
			CCPoint lastPt = ptMe;

			if (ptMe.x > ptAim.x)
			{
				ptMe.x -= dt * xSpeed;
			}
			else
			{
				ptMe.x += dt * xSpeed;
			}

			if (ptMe.y > ptAim.y)
			{
				ptMe.y -= dt * ySpeed;
			}
			else
			{
				ptMe.y += dt * ySpeed;
			}
			m_curPos = ptMe;
			info.pMe->setPosition(ptMe);
			CCRect rect;
			if (lastPt.x > ptMe.x)
			{
				rect.setRect(ptMe.x, ptMe.y, fabsf(lastPt.x - ptMe.x), fabsf(lastPt.y - ptMe.y));
			}
			else
			{
				rect.setRect(lastPt.x, lastPt.y, fabsf(lastPt.x - ptMe.x), fabsf(lastPt.y - ptMe.y));
			}
			//判断是否过
			if (rect.containsPoint(ptAim))
			{
				info.pCallBack->startWithTarget(info.pMe);
				info.pCallBack->execute();
				info.pCallBack->release();
				//移除弹道特效
				info.pMe->removeFromParent();
				info.pMe->release();
				m_skillEffectPostionInfo.erase(itr++);
				continue;
			}
		}
		else if (info.eType == ESEF_Follow)
		{
			m_curPos = info.pMe->getPosition();
			info.pMe->setPosition(m_curPos);
		}

		++itr;
	}
}



bool GameSkill::isInCD()
{
	return m_nCDTimer < m_nCD;
}

void GameSkill::resetCD()
{
	m_nCDTimer = 0;
}

const TemplateSkill* GameSkill::GetTemplate() const
{
	GameWorld* pGameWorld = GAMEWORLD;
	return pGameWorld->get<TemplateSkill>(m_nSN);
}

void GameSkill::playSoundEffect( TSkillEffectType eType )
{
	if (!m_aSoundEffect[eType].empty())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(m_aSoundEffect[eType].c_str());
	}
}


int32t GameSkill::calHurtPoint( int32t nAimSN, int32t nSelftSN )
{
	string luaFunc = GetTemplate()->getScriptfunc();
	LUAHELPER->pushInt(nAimSN);
	LUAHELPER->pushInt(nSelftSN);
	LUAHELPER->pushInt(m_nSN);
	int32t nVal = LUAHELPER->executeGlobalFunction(luaFunc.c_str(), 3)["val"].asInt();
	return nVal;
}

void GameSkill::onExit()
{
	stopAllAction();
}

void GameSkill::removeFromSkillEffectPostionInfo( cocos2d::CCNode* pMe )
{
	for (std::list<SkillEffectPostionInfo>::iterator itr = m_skillEffectPostionInfo.begin(); itr != m_skillEffectPostionInfo.end();)
	{
		SkillEffectPostionInfo& info = *itr;
		if (info.pMe == pMe)
		{
			m_skillEffectPostionInfo.erase(itr++);
		}
		else
		{
			++itr;
		}
	}
}



