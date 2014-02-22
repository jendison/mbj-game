#include "UILayerGameBattle.h"
#include "Macro.h"
#include "GameBattleLayer.h"
#include "GameWorld.h"
#include "GameScene.h"
#include "TemplateBuilding.h"

using namespace cocos2d::gui;

UILayerGameBattle::UILayerGameBattle()
{

}

UILayerGameBattle::~UILayerGameBattle()
{

}

UILayerGameBattle* UILayerGameBattle::create()
{
	UILayerGameBattle* p = new UILayerGameBattle();
	if (p && p->init())
	{
		p->autorelease();
		return p;
	}

	CC_SAFE_DELETE(p);
	return p;
}

bool UILayerGameBattle::init()
{
	CCLayer::init();
	UILayer* pLayer = UILayer::create();
	this->addChild(pLayer);

	m_pBattleUIJson = GUIReader::shareReader()->widgetFromJsonFile("UI/main_1.json");
	GAME_ASSERT_RET(m_pBattleUIJson, false, ("load UILayerGameBattle fail"));
	m_pBattleUIJson->setTag(1);
	m_pBattleUIJson->scheduleUpdate();
	pLayer->addWidget(m_pBattleUIJson);

	// examples initialize
	UIPanel* button_panel = dynamic_cast<UIPanel*>(UIHelper::seekWidgetByName(m_pBattleUIJson, "Panel")); 
	GAME_ASSERT_RET(button_panel, false, ("load UILayerGameBattle Panel fail"));

	UIButton* equip_btn =  dynamic_cast<UIButton*>(UIHelper::seekWidgetByName(m_pBattleUIJson, "arm1"));
	GAME_ASSERT_RET(equip_btn, false, ("load UILayerGameBattle arm1 fail"));
	equip_btn->setEnabled(true);
	equip_btn->setTouchEnabled(true);

	equip_btn->addTouchEventListener(this, toucheventselector(UILayerGameBattle::menuArmCallback));

	UIButton* equip_btn2 = dynamic_cast<UIButton*>(UIHelper::seekWidgetByName(m_pBattleUIJson, "arm2"));
	GAME_ASSERT_RET(equip_btn, false, ("load UILayerGameBattle arm2 fail"));
	equip_btn2->setBright(false);
	equip_btn2->setTouchEnabled(false);

	equip_btn2->addTouchEventListener(this, toucheventselector(UILayerGameBattle::menuArmCallback));

	UIButton* pBuild1 = dynamic_cast<UIButton*>(UIHelper::seekWidgetByName(m_pBattleUIJson, "building1"));
	GAME_ASSERT_RET(pBuild1, false, ("load UILayerGameBattle building1 fail"));

	pBuild1->setBright(false);
	pBuild1->addTouchEventListener(this, toucheventselector(UILayerGameBattle::menuBuildingCallback));

	UIButton* pBuild2 = dynamic_cast<UIButton*>(UIHelper::seekWidgetByName(m_pBattleUIJson, "building2"));
	pBuild2->setBright(false);

	return true;
}

void UILayerGameBattle::menuBuildingCallback( CCObject* pSender, TouchEventType eType )
{
	if (eType != TouchEventType::TOUCH_EVENT_ENDED)
	{
		return;
	}

	UIWidget* example_root = dynamic_cast<UIPanel*>(getChildByTag(1));
	UIPanel* button_panel = dynamic_cast<UIPanel*>(example_root->getChildByName("Panel")); 
	UIButton* pArm2 = dynamic_cast<UIButton*>(button_panel->getChildByName("arm2"));
	pArm2->setEnabled(true);
}

void UILayerGameBattle::menuArmCallback( CCObject* pSender, TouchEventType eType )
{
	if (eType != TouchEventType::TOUCH_EVENT_ENDED)
	{
		return;
	}

	UIButton* pBtn = (UIButton*)pSender;
	std::string str = pBtn->getName();
	if (str == "arm1")
	{
		BATTLELAYER->playerAddSprite(10000);
	}
	else
	{
		BATTLELAYER->playerAddSprite(10001);
	}
}

void UILayerGameBattle::upateRes( int32t nVal )
{
	UILabelBMFont* pLabel = dynamic_cast<UILabelBMFont*>(UIHelper::seekWidgetByName(m_pBattleUIJson, "resStr"));
	pLabel->setText(CCString::createWithFormat("res:%d", nVal)->getCString());

	//building1

	UIPanel* button_panel = dynamic_cast<UIPanel*>(UIHelper::seekWidgetByName(m_pBattleUIJson,"Panel")); 

	UIButton* pBuild1 = dynamic_cast<UIButton*>(UIHelper::seekWidgetByName(m_pBattleUIJson,"building1"));

	const TemplateBuilding* pTempBuild1 = GAMEWORLD->get<TemplateBuilding>(30000);
	if (pTempBuild1->getCost().CostType == TCostType_res)
	{
		if (nVal >pTempBuild1->getCost().CostNum )
		{
			pBuild1->setEnabled(true);
		}
	}

	UIButton* pBuild2 = dynamic_cast<UIButton*>(UIHelper::seekWidgetByName(m_pBattleUIJson,"building2"));
	if (nVal > 200)
	{
		pBuild2->setEnabled(true);
	}
}
