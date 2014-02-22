
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UILayerStart.h"
#include "UILayerMap.h"

USING_NS_CC;
USING_NS_CC_EXT;

UILayerStart::UILayerStart(void)
{
	m_pUILayer=NULL;
}


UILayerStart::~UILayerStart(void)
{
}
bool UILayerStart::init()
{
	if (CCLayer::init())
	{

		m_pUILayer = UILayer::create();
		m_pUILayer->scheduleUpdate();
		this->addChild(m_pUILayer);

		// page root from json
		Layout* page_root = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("dota_3.ExportJson"));
		m_pUILayer->addWidget(page_root);

		UIButton *btn_map = dynamic_cast<UIButton*>(m_pUILayer->getWidgetByName("btn_map"));

		btn_map->addReleaseEvent(this, coco_releaseselector(UILayerStart::btn_mapCallback));
		
		


		return true;
	}
	return false;


}

void UILayerStart::btn_mapCallback(CCObject* sender)
{
	m_pUILayer->unscheduleUpdate();
	m_pUILayer->removeFromParent();
	CCScene * pScene = CCScene::create();
	CCLayer * pLayer =  UILayerMap::create();
	pScene->addChild(pLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}