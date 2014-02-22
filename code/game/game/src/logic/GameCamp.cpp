#include <cocos2d.h>
#include "GameCamp.h"
#include "GameWorld.h"
#include "../template/TemplateCamp.h"

GameCamp::GameCamp()
{
	m_nRes = 0; //资源数量
	m_nCD = 0;	//资源增长cd
	m_nIncreateVal = 0;	//增长数值
	m_nCoreArm = 0;

	m_nSN = 0;
}
GameCamp::~GameCamp()
{

}

GameCamp* GameCamp::create(int32t nSN)
{
	GameCamp* p = new GameCamp();
	if (p && p->initWithGame(nSN))
	{
		return p;
	}

	delete p;
	p = NULL;
	return NULL;
}

bool GameCamp::initWithGame( int32t nSN )
{
	GameWorld* pGameWorld = GAMEWORLD;
	const TemplateCamp* pCamp = pGameWorld->get<TemplateCamp>(nSN);
	GAME_ASSERT_RET(pCamp, false, ("invalid data, plz check data.zip!"));
	
	do 
	{
		m_nRes = pCamp->getInitresouce();
		m_nCD = pCamp->getResouceinccd();
		m_nIncreateVal = pCamp->getResouceincnum();
		m_nCoreArm = pCamp->getCorearm();
		m_nSN = nSN;
		return true;
	} while (0);

	return false;
}

