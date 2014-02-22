#include "GameAnimation.h"
#include "Macro.h"
#include <cocoa/CCArray.h>
#include <sprite_nodes/CCSpriteFrame.h>
#include <sprite_nodes/CCSpriteFrameCache.h>
#include <sprite_nodes/CCAnimation.h>
#include <sprite_nodes/CCSprite.h>
#include <actions/CCAction.h>

using namespace cocos2d;
using namespace cocos2d::extension;

GameAnimtion::GameAnimtion()
{
	memset(m_pCallBack, 0, _countof(m_pCallBack) * sizeof(CCCallFuncND*));
}

GameAnimtion::~GameAnimtion()
{

}


GameAnimtion*  GameAnimtion::create( const char* fileName)
{
	GameAnimtion* p = new GameAnimtion();
	if (p && p->init(fileName))
	{
		p->autorelease();
		return p;
	}
	
	CC_SAFE_DELETE(p);
	return NULL;
}

bool GameAnimtion::init( const char* fileName )
{
	return  CCArmature::init(fileName);
}


void GameAnimtion::onExit()
{
	CCArmatureAnimation* pAnimation = getAnimation();
	GAME_ASSERT_RET(pAnimation, ;, ( "animation not find"));
	pAnimation->setMovementEventCallFunc(NULL, NULL);
}


bool GameAnimtion::play(const char* strActionName, cocos2d::CCCallFuncND* onStatusEnd,  bool repeat/* = false */)
{
	CCArmatureAnimation* pAnimation = getAnimation();
	GAME_ASSERT_RET(pAnimation, false, ( "animation not find"));

	if (onStatusEnd)
	{
		GAME_ASSERT_RET(!repeat, false, ( "animation loop can not run callback"));
		pAnimation->setMovementEventCallFunc(this, movementEvent_selector(GameAnimtion::onPlayComplete));
		int32t index = pAnimation->getIndexByAnimationName(strActionName);
		GAME_ASSERT_RET(index < 20, false, ( "out of range"));
		m_pCallBack[index] = onStatusEnd;
		onStatusEnd->retain();
	}

	getAnimation()->play(strActionName, -1, -1, repeat ? 1 : 0);
	return true;

}

bool GameAnimtion::play( int32t index, cocos2d::CCCallFuncND* onStatusEnd /*= NULL*/,  bool repeat/* = false */)
{
	CCArmatureAnimation* pAnimation = getAnimation();
	string name = pAnimation->getAnimationNameByIndex(index);
	return play(name.c_str(), onStatusEnd, repeat);
}

void GameAnimtion::onPlayComplete( CCArmature* pArmature, MovementEventType eMovementEventType, const char* strAnimationName )
{
	if (eMovementEventType == COMPLETE || eMovementEventType == LOOP_COMPLETE)
	{
		CCArmatureAnimation* pAnimation = getAnimation();
		int32t index = pAnimation->getIndexByAnimationName(strAnimationName);
		GAME_ASSERT_RET(index < 20, ;, ( "out of rage"));

		cocos2d::CCCallFuncND* onStatusEnd = m_pCallBack[index];
		if (onStatusEnd)
		{
			onStatusEnd->startWithTarget(pArmature);
			onStatusEnd->execute();
			onStatusEnd->release();
			onStatusEnd = NULL;
			m_pCallBack[index] = nullptr;
		}
	}
}
