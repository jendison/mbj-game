#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class UILayerStart : public CCLayer
{
public:
	UILayerStart(void);
	~UILayerStart(void);

	bool init();
	virtual void btn_mapCallback(CCObject* sender);	

public:
	CREATE_FUNC(UILayerStart);

private:
	UILayer* m_pUILayer;
};

