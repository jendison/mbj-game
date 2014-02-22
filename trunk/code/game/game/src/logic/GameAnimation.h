#include "Macro.h"
#include "GameSprite.h"

#ifndef __GAMEANIMATION_H__
#define __GAMEANIMATION_H__

namespace cocos2d
{
	class CCAnimation;
	class CCSprite;
	class CCAction;
}

//��Ϸ���ƶ�����
class GameAnimtion : public cocos2d::extension::CCArmature
{
public:
	GameAnimtion();
	virtual ~GameAnimtion();

	//����һ������
	static GameAnimtion* create(const char* fileName);

	//����һ������
	bool play(const char* strActionName,  cocos2d::CCCallFuncND* onStatusEnd = NULL, bool repeat = false);
	bool play(int32t index,  cocos2d::CCCallFuncND* onStatusEnd = NULL, bool repeat = false);

	//����������ɻص�
	void onPlayComplete(cocos2d::extension::CCArmature* pArmature, cocos2d::extension::MovementEventType eMovementEventType, const char* strAnimationName );
	void onExit();

private:
	bool init(const char* fileName);

private:
	cocos2d::CCCallFuncND* m_pCallBack[20];//ÿ������������ɵĻص�
};


#endif