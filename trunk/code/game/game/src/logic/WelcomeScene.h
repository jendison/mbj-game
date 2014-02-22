#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameSprite.h"

#ifndef __WELCOMESCENE_H__
#define  __WELCOMESCENE_H__
using namespace cocos2d::gui;

//”Œœ∑ª∂”≠ ≥°æ∞
class WelcomeScene : public cocos2d::CCScene
{
public:
	WelcomeScene():m_pCurNode(NULL){}
	~WelcomeScene();

	bool init();
	static WelcomeScene* create();

	void menuStartCallback(CCObject* pSender, TouchEventType eType);
	void menuDeveloperCallback(CCObject* pSender);
	void menuExitCallback(CCObject* pSender);
	void menuTestCallback(CCObject* pSender);

private:
	cocos2d::CCNode* m_pCurNode;
};


#endif //__GAMERESULTSCENE_H__
