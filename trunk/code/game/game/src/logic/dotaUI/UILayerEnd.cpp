
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UILayerEnd.h"
#include "UILayerupLevel.h"

USING_NS_CC;
USING_NS_CC_EXT;

UILayerEnd::UILayerEnd(void)
{
	m_pUILayer=NULL;
}


UILayerEnd::~UILayerEnd(void)
{

}

bool UILayerEnd::init()
{
	if (CCLayer::init())
	{

		m_pUILayer = UILayer::create();
		m_pUILayer->scheduleUpdate();
		this->addChild(m_pUILayer);

		// page root from json
		Layout* pPageRoot = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("dota_5.ExportJson"));
		m_pUILayer->addWidget(pPageRoot);

		UIButton *btn_upLevel = dynamic_cast<UIButton*>(m_pUILayer->getWidgetByName("btn_upLevel"));

		btn_upLevel->addReleaseEvent(this, coco_releaseselector(UILayerEnd::btn_upLevelCallback));

		return true;
	}
	return false;


}

void UILayerEnd::btn_upLevelCallback(CCObject* sender)
{
	m_pUILayer->unscheduleUpdate();
	m_pUILayer->removeFromParent();
	CCScene * pScene = CCScene::create();
	CCLayer * pLayer =  UILayerUpLevel::create();
	pScene->addChild(pLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}
