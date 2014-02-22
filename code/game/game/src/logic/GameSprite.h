#include "Macro.h"
#include <string>
#include "cocoa/CCObject.h"
#include <cocoa/CCGeometry.h>
#include <sprite_nodes/CCSprite.h>
#include "GameSkill.h"
#include "TypeDefine.h"
#include <vector>
#ifndef __GAMESPRITE_H__
#define __GAMESPRITE_H__
using std::vector;

namespace cocos2d
{
	class CCSpriteBatchNode;
	class CCNode;
	class CCCallFuncND;
}

class GameAnimtion;
class GameBattleLayer;

enum ESpriteStatus	//精灵的状态
{
	ESS_Standing = 0,	//站立
	ESS_Attacking,		//攻击
	ESS_Runnig,			//跑步
	ESS_Dying,			//死亡
	ESS_Attacked,		//被攻击
	ESS_Cnt
};

enum ESpriteDir	//精灵朝向
{
	ESD_Left = 0,
	ESD_Right,
	ESD_Cnt
};

enum ESpriteCamp
{
	ESC_Player = 0,
	ESC_AI,
	ESC_Cnt
};

class GameSprite : public cocos2d::CCNode
{
public:
	GameSprite();
	~GameSprite();

	static GameSprite* create(int32t nSN);

	bool initWithGame(int32t nSN);

	int32t getSN() const {return m_nSN;}
	bool setStatus(ESpriteStatus eStatus, cocos2d::CCCallFuncND* onStatusEnd = NULL);
	ESpriteStatus getStatus() const {return m_eStatus;}
	void setCamp(ESpriteCamp eCamp) { m_eCamp = eCamp;};
	ESpriteCamp getCamp() {return m_eCamp;}
	bool moveto(const cocos2d::CCPoint& postion, float fSpeed, cocos2d::CCCallFuncND*  onMoveDone);
	bool fightWith(GameSprite* pAim, cocos2d::CCCallFuncND*  onFightDone);
	bool setDir(ESpriteDir  eDir);
	ESpriteDir getDir() const {return m_eDir;}

	const cocos2d::CCPoint&  getSpritePosition() {return getPosition();}
	float getSpritePositionX() {return getPositionX();}

	GameSkill* selectASkill();//选择一个技能
	void onHurt(int nPoint);
	bool isDead();
	void draw();
	void drawHealthBar();

	void doActivate(float dt);
	void doDead(cocos2d::CCNode* pNode, void*);

	void update(float delta);
	void updateSkill(float dt);

	//call back
	void callback_skillEffectCastPlayOver(cocos2d::CCNode* pNode, void*p);	//施展技能播放完成
	void callback_skillEffectHitPlayOver(cocos2d::CCNode* pNode, void*p);	//施展效果播放完成
	void callback_skillEffectTrajectoryPlayOver(cocos2d::CCNode* pNode, void*p);	//施展弹道效果播放完成

	void callback_AttackEnd(cocos2d::CCNode* pNode, void*p);

	void callback_palySkillEffect(cocos2d::CCNode* pNode, void*p);
	void setSpriteScale(float f) {setScale(f);}

	virtual bool isCanRun() {return true;}
	virtual bool isHero() {return false;}
	TAimMoveType getMoveType() const {return m_eMoveType;}
	void onExit();
private:
	GameSprite* selectAim(GameSkill* pSkill);	//根据技能选中目标
	GameSkill* getSkill(int32t nSkill);

protected:
	std::string m_strSpriteFilePath;

	ESpriteStatus m_eStatus;					//精灵状态
	GameAnimtion* m_pGameAnimation;				//动画

	ESpriteDir m_eDir;	//精灵朝向

	int m_nHP;		//
	int m_nCD;		//
	float m_fSpeed;	//	
	int m_nCostNum;	//消耗资源的数量
	ESpriteCamp m_eCamp;	//所属阵营
	int m_nMaxHP;

	vector<GameSkill*> m_pSkillList;	//技能
	bool m_bIsActive;
	int32t m_nSN;	//精灵归属SN
	TAimMoveType m_eMoveType;

	bool	m_bIsInCastSkillStatus;	//是否在施展技能的状态里
	float m_fBirthTime;

#if _DEBUG
	GameSkill* m_pCurrentSkill;
#endif
};

#endif // !__GAMESPRITE_H__
