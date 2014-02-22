#include "cocos2d.h"
#include "cocos-ext.h"

#ifndef __UILAYEREND_H__
#define  __UILAYEREND_H__

USING_NS_CC;
USING_NS_CC_EXT;

class UILayerEnd : public CCLayer
{
public:
	UILayerEnd(void);
	~UILayerEnd(void);
	
	bool init();
	CREATE_FUNC(UILayerEnd);
	virtual void btn_upLevelCallback(cocos2d::CCObject* sender);	

private:
	UILayer* m_pUILayer;
};

#endif //__UILAYEREND_H__
