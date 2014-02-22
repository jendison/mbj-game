#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameSprite.h"

#ifndef __GAMERESULTSCENE_H__
#define  __GAMERESULTSCENE_H__
using namespace cocos2d::gui;

class GameResultScene : public cocos2d::CCScene
{
public:
	GameResultScene() : m_fTimer(0) {}
	bool init(ESpriteCamp eCamp);
	static GameResultScene* create(ESpriteCamp eCamp);

	void changeScene(float dt);
	void update(float dt);
private:
	UILayer* m_pUILayer;
	bool bWin;
	UILayer* m_pUI;
	float m_fTimer;
};

#endif //__GAMERESULTSCENE_H__
