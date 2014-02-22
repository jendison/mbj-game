#include "TypeDefine.h"
#include <string>
#include "../template/TemplateCommon.h"
#include "cocos2d.h"
#include "../template/TemplateSkill.h"

#ifndef __GAMESKILL_H__
#define __GAMESKILL_H__
class GameBattleLayer;
class GameSprite;

enum ESkillEffectFlow
{
	ESEF_Moveto = 0,	//移动到目标
	ESEF_Follow = 1,	//跟随
};

struct SkillEffectPostionInfo
{
	SkillEffectPostionInfo(ESkillEffectFlow _eType) : pAim(NULL), pCallBack(NULL), pMe(NULL), eType(_eType) {}
	cocos2d::CCNode* pAim;	//目标
	cocos2d::CCNode* pMe;	//具体的技能特效
	cocos2d::CCCallFuncND* pCallBack;
	ESkillEffectFlow eType;
};

class GameAnimtion;
class GameSkill : public cocos2d::CCObject
{
public:
	GameSkill();
	~GameSkill();
	
	static GameSkill* create( int32t nSN);

	bool initWithGame(int32t nSN);

public:
	bool	isTrajectory() {return !m_aAnimationsEffect[TSkillEffectType_trajectory].empty();}
	//计算伤害点数
	int32t calHurtPoint(int32t nAimSN, int32t nSelftSN);
	//技能生效范围
	int32t getDistance() const {return GetTemplate()->getDistance();}
	//播放施展特效
	void	playEffect_cast(cocos2d::CCCallFuncND* pCallBack, const cocos2d::CCPoint& pos);
	void	callback_playEffect_cast(cocos2d::CCNode* pNode, void* p);

	//播放弹道效果
	void	playEffect_trajectory(cocos2d::CCCallFuncND* pCallBack, const cocos2d::CCPoint& srcPoint, GameSprite* pAimSprite, float fSpeed);	
	void	callback_playEffect_trajectory(cocos2d::CCNode* pNode, void* p);

	//播放击中效果
	void	playEffect_hit(GameSprite* pSprite, const vector<GameSprite*>&  aimSprite);	
	void	callback_playEffect_hit(cocos2d::CCNode* pNode, void* p);

	void	update(float dt);

public:
	bool	isInCD();
	void	resetCD();	//重置技能CD
	int32t  getCD() const {return m_nCD;}
	void	setCD(int32t t) {m_nCD = t;}

	float	getTrajectorySpeed() const {return GetTemplate()->getTrajectoryspeed();}

	int32t getStartPlaySkillEffectTime() const {return GetTemplate()->getStartplayskilleffecttime();}
	void	playSoundEffect(TSkillEffectType eType);

	void	stopAllAction();
	void	onExit();

	int32t getSN() const {return m_nSN;}
	const TemplateSkill* GetTemplate() const;
	const cocos2d::CCPoint& getSkillSpritePostion() {return m_curPos;};

private:
	const string& getSoundEffect() const;
	void removeFromSkillEffectPostionInfo(cocos2d::CCNode* pMe);

private:
	int32t m_nSN;
	GameBattleLayer* m_pGame;
	int32t m_nCD;					//CD
	int32t m_nPoint;				//伤害点数
	std::string m_strDamageLuaFunc;	//计算伤害的lua函数

	std::string m_aSoundEffect[TSkillEffectType_Cnt];			//音效
	std::string m_aAnimationsEffect[TSkillEffectType_Cnt];		//特效

	std::list<SkillEffectPostionInfo> m_skillEffectPostionInfo;	//播放技能的特效的位置信息
	int32t m_nCDTimer;				//CD计时器
	cocos2d::CCPoint m_curPos;	//技能当前位置
};

#endif //__GAMESKILL_H__