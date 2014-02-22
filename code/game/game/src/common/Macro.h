#include <include/ccMacros.h>
#include "AppDelegate.h"
#include "common/Common.h"
#include "../CCPlatformMacros.h"

#ifndef __MACRO_H__
#define __MACRO_H__

#ifndef GAMEMAX
#define GAMEMAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#define GAME_ASSERT_RET(cond, failReturn, msg) \
	do \
{ \
	int _r_ = (int)(cond); \
	if (_r_ == 0) \
	{ \
	cocos2d::CCString* str = cocos2d::CCString::createWithFormat msg;	\
	CCAssert(_r_ && #cond, str->getCString());	\
	return failReturn;\
	}	\
} while (0);

#define  GAMEWORLD ((AppDelegate*)cocos2d::CCApplication::sharedApplication())->getGameWorld()
#define  LUAHELPER ((AppDelegate*)cocos2d::CCApplication::sharedApplication())->getLuaHelper()
#define	 GAMESCENE GAMEWORLD->getCurrentScene()
#define  BATTLELAYER GAMESCENE->getBattleLayer()
#define	 UIBATTLELAYER  GAMESCENE->getUIBattleLayer()

#define CREATE_CALLBACK_ARG_2(arg1, arg2)	\
CallBackArg* pArg = new CallBackArg(); \
GAME_ASSERT_RET(pArg, ;, ( "new fail")); \
pArg->nArgs = 2; \
pArg->args[0] = arg1; \
pArg->args[1] = arg2;


#endif//__MACRO_H__