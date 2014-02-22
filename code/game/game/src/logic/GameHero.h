#ifndef __GAMEHERO_H__
#define __GAMEHERO_H__

#include "GameSprite.h"
#include "TypeDefine.h"


class GameHero : public GameSprite
{
public:
	GameHero();
	~GameHero();
	static GameHero* create(int32t nSN, GameBattleLayer* pGame );
	bool initWithGame(int32t nSN,GameBattleLayer* pGame);
	bool isCanRun() {return m_bIsCanRun;};
	void setIsCanRun(bool b) {m_bIsCanRun = b;}
	void update(float delta);
	virtual bool isHero() {return true;}
	void flowBy(cocos2d::CCNode* pNode);
	void releaseFlow(cocos2d::CCNode* pNode);

	void incMoney(int nDelta) {m_nMoney += nDelta;}
	void incEnery(int nDelta) {m_nEnery += nDelta;}

private:
	bool m_bIsCanRun;	//�Ƿ����ƶ���
	int32t m_nMoney;	//��Ǯ
	int32t m_nEnery;	//����
};

#endif //__GAMEHERO_H__