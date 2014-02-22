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

//游戏定制动画类
class GameAnimtion : public cocos2d::extension::CCArmature
{
public:
	GameAnimtion();
	virtual ~GameAnimtion();

	//创建一个动画
	static GameAnimtion* create(const char* fileName);

	//播放一个动画
	bool play(const char* strActionName,  cocos2d::CCCallFuncND* onStatusEnd = NULL, bool repeat = false);
	bool play(int32t index,  cocos2d::CCCallFuncND* onStatusEnd = NULL, bool repeat = false);

	//动画播放完成回调
	void onPlayComplete(cocos2d::extension::CCArmature* pArmature, cocos2d::extension::MovementEventType eMovementEventType, const char* strAnimationName );
	void onExit();

private:
	bool init(const char* fileName);

private:
	cocos2d::CCCallFuncND* m_pCallBack[20];//每个动作播放完成的回调
};


#endif