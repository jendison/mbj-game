#include "AppDelegate.h"
#include "../template/TemplateMgr.h"
#include "GameSprite.h"

#ifndef __GAME_WORLD_H__
#define __GAME_WORLD_H__

class GameCamp;
class GameScene;
class GameWorld
{
public:
	GameWorld(void);
	~GameWorld(void);

	bool Init();
	void Run();
	bool Stop();

	GameScene* getCurrentScene() const {return m_pScene;}
	void setCurrentScene(GameScene* p) {m_pScene = p;}
	template<class T>
	const T* get(int32t nSN)
	{
		if (pTemplateMgr == NULL)
		{
			pTemplateMgr = new TemplateMgr;
			if(!pTemplateMgr->Init())
			{
				return NULL;
			}
		}
		return pTemplateMgr->get<T>(nSN);
	}

	GameCamp* getCamp(ESpriteCamp eCamp) {return eCamp == ESC_Player ? m_pPlayerCamp : m_pAICamp;}
	int32t getIncRes() const {return m_nIncRes;}

private:
	TemplateMgr* pTemplateMgr;
	int32t m_nIncRes;		//系统每秒给的资源数
	GameCamp* m_pAICamp;
	GameCamp* m_pPlayerCamp;
	GameScene* m_pScene; //游戏场景
};

#endif //__GAME_WORLD_H__