#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
//#include <CCScrollView/CCScrollView.h>

#include "Macro.h"
#include "GameSprite.h"
#include "GameHero.h"

class GameAnimtion;
class GameSprite;
class TemplateScene;
using namespace cocos2d::gui;

class GameBattleLayer : public cocos2d::CCLayer
{
public:
	enum EBattleLayerdActionTag
	{
		EHelloWorldActionTag_FollowHero = 1,	//跟随主角动作
	};
	GameBattleLayer();
	~GameBattleLayer();

    virtual bool init();  
    CREATE_FUNC(GameBattleLayer);

public:
	 void scrollViewDidScroll(cocos2d::extension::CCScrollView * view);
	 void scrollViewDidZoom(cocos2d::extension::CCScrollView * view);

	 void onEnter();

	 virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	 virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	 virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	 virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	 void update(float dt);

	 void playerAddSprite(int32t nArmSN);

	 	//技能生效,返回受攻击的精灵
	 vector<GameSprite*> onSkillEffect(GameSprite* pSprite, GameSkill* pSkill);

	 //根据技能选择目标
	GameSprite* selectAim(GameSprite* pSprite, GameSkill* pSkill);
	 virtual void onExit();

public:
	 CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, m_aEnemies, Enemies);	//敌方
	 CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, m_aArms, Arms);		//己方
	 CC_SYNTHESIZE_RETAIN(GameHero*, m_pHero, Hero);				//英雄

public:
	void loadWave();	//加载一波敌对精灵
	//加载核心建筑
	bool loadCoreArm(ESpriteCamp eCamp, ESpriteDir eDir);
	//加载英雄
	bool loadHero(int nSN);

	void onSpriteDead(GameSprite* sprite);

	int32t getCurrentRes() const {return m_nRes;}

	void incRes(float dt);

	// a selector callback
	void menuArmCallback(CCObject* pSender);

	void menuBuildingCallback(CCObject* pSender);

private:
	//创建一个精灵
	GameSprite* createSprite(int32t nSN, ESpriteCamp eCamp, ESpriteDir eDir, float activeTime);
	void changeResNum(int32t nRes);

	void changeMoneyNum(int32t nMoeny);
	void changeEneryNum(int32t nEnery);

	void giveDrop(int32t nArmSN);	//给掉落

	void onCompleteScene(ESpriteCamp eCamp, int32t nSpriteSN);

private:
	int32t m_nRes;						//当前资源数量
	cocos2d::CCPoint m_ptTouch;
};

#endif  // __HELLOWORLD_SCENE_H__