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
		EHelloWorldActionTag_FollowHero = 1,	//�������Ƕ���
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

	 	//������Ч,�����ܹ����ľ���
	 vector<GameSprite*> onSkillEffect(GameSprite* pSprite, GameSkill* pSkill);

	 //���ݼ���ѡ��Ŀ��
	GameSprite* selectAim(GameSprite* pSprite, GameSkill* pSkill);
	 virtual void onExit();

public:
	 CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, m_aEnemies, Enemies);	//�з�
	 CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, m_aArms, Arms);		//����
	 CC_SYNTHESIZE_RETAIN(GameHero*, m_pHero, Hero);				//Ӣ��

public:
	void loadWave();	//����һ���жԾ���
	//���غ��Ľ���
	bool loadCoreArm(ESpriteCamp eCamp, ESpriteDir eDir);
	//����Ӣ��
	bool loadHero(int nSN);

	void onSpriteDead(GameSprite* sprite);

	int32t getCurrentRes() const {return m_nRes;}

	void incRes(float dt);

	// a selector callback
	void menuArmCallback(CCObject* pSender);

	void menuBuildingCallback(CCObject* pSender);

private:
	//����һ������
	GameSprite* createSprite(int32t nSN, ESpriteCamp eCamp, ESpriteDir eDir, float activeTime);
	void changeResNum(int32t nRes);

	void changeMoneyNum(int32t nMoeny);
	void changeEneryNum(int32t nEnery);

	void giveDrop(int32t nArmSN);	//������

	void onCompleteScene(ESpriteCamp eCamp, int32t nSpriteSN);

private:
	int32t m_nRes;						//��ǰ��Դ����
	cocos2d::CCPoint m_ptTouch;
};

#endif  // __HELLOWORLD_SCENE_H__