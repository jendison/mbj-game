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

enum ESpriteStatus	//�����״̬
{
	ESS_Standing = 0,	//վ��
	ESS_Attacking,		//����
	ESS_Runnig,			//�ܲ�
	ESS_Dying,			//����
	ESS_Attacked,		//������
	ESS_Cnt
};

enum ESpriteDir	//���鳯��
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

	GameSkill* selectASkill();//ѡ��һ������
	void onHurt(int nPoint);
	bool isDead();
	void draw();
	void drawHealthBar();

	void doActivate(float dt);
	void doDead(cocos2d::CCNode* pNode, void*);

	void update(float delta);
	void updateSkill(float dt);

	//call back
	void callback_skillEffectCastPlayOver(cocos2d::CCNode* pNode, void*p);	//ʩչ���ܲ������
	void callback_skillEffectHitPlayOver(cocos2d::CCNode* pNode, void*p);	//ʩչЧ���������
	void callback_skillEffectTrajectoryPlayOver(cocos2d::CCNode* pNode, void*p);	//ʩչ����Ч���������

	void callback_AttackEnd(cocos2d::CCNode* pNode, void*p);

	void callback_palySkillEffect(cocos2d::CCNode* pNode, void*p);
	void setSpriteScale(float f) {setScale(f);}

	virtual bool isCanRun() {return true;}
	virtual bool isHero() {return false;}
	TAimMoveType getMoveType() const {return m_eMoveType;}
	void onExit();
private:
	GameSprite* selectAim(GameSkill* pSkill);	//���ݼ���ѡ��Ŀ��
	GameSkill* getSkill(int32t nSkill);

protected:
	std::string m_strSpriteFilePath;

	ESpriteStatus m_eStatus;					//����״̬
	GameAnimtion* m_pGameAnimation;				//����

	ESpriteDir m_eDir;	//���鳯��

	int m_nHP;		//
	int m_nCD;		//
	float m_fSpeed;	//	
	int m_nCostNum;	//������Դ������
	ESpriteCamp m_eCamp;	//������Ӫ
	int m_nMaxHP;

	vector<GameSkill*> m_pSkillList;	//����
	bool m_bIsActive;
	int32t m_nSN;	//�������SN
	TAimMoveType m_eMoveType;

	bool	m_bIsInCastSkillStatus;	//�Ƿ���ʩչ���ܵ�״̬��
	float m_fBirthTime;

#if _DEBUG
	GameSkill* m_pCurrentSkill;
#endif
};

#endif // !__GAMESPRITE_H__
