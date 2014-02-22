#include "cocos2d.h"
#include "cocos-ext.h"
#include "TypeDefine.h"

#ifndef __UILAYERGAMEBATTLE_H__
#define __UILAYERGAMEBATTLE_H__

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class UILayerGameBattle : public CCLayer
{
public:
	UILayerGameBattle();
	~UILayerGameBattle();

	static UILayerGameBattle* create();

	bool init();

public:
	void menuBuildingCallback(CCObject* pSender, TouchEventType eType);
	void menuArmCallback(CCObject* pSender, TouchEventType eType);

public:
	void upateRes(int32t nVal);

public:

private:
	UIWidget* m_pBattleUIJson;
};

#endif //