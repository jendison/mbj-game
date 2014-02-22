#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include <cocos2d.h>
#include "../template/TemplateCommon.h"
using namespace cocos2d::gui;
class GameBattleLayer;
class UILayerGameBattle;

class GameScene : public cocos2d::CCScene
{
public:
	GameScene();
	~GameScene();
	static GameScene* create(int32t nSN);

	GameBattleLayer* getBattleLayer() const {return m_pBattleLayer;}
	UILayerGameBattle* getUIBattleLayer() const {return m_pUIBattleLayer;}

	int32t getSN() const {return m_nSN;}
	int32t getNextSceneSN() const {return m_nNextScene;}
public:
	const cocos2d::CCPoint& getSpritePlayerBronPoint(TAimMoveType eType){ return m_ptSpritePlayer[eType];}
	const cocos2d::CCPoint& getSpriteAIBronPoint(TAimMoveType eType){ return m_ptSpriteAI[eType];}
	cocos2d::CCSize getMapSize() { return m_pMap->getMapSize();}
	cocos2d::CCSize getTileSize() {return m_pMap->getTileSize();}
	cocos2d::CCTMXTiledMap* getMap() const {return m_pMap;}

	virtual void onEnter();

private:
	bool init(int32t nSN);

	bool loadMainUI();
	bool loadMap();
	void loadArmature( const char* str );
	bool LoadResource();

private:
	GameBattleLayer* m_pBattleLayer;		//ս����
	UILayerGameBattle* m_pUIBattleLayer;	//ս��UI��
	int32t m_nSN;	//����SN
	int32t m_nNextScene;	//��һ��SN

	cocos2d::CCTMXTiledMap* m_pMap;							//��ͼ�ļ�
	cocos2d::CCPoint m_ptSpriteAI[TAimMoveType_Cnt];		//AI��Ӫ�ĳ�����
	cocos2d::CCPoint m_ptSpritePlayer[TAimMoveType_Cnt];	//�����Ӫ�ĳ�����
};

#endif //__GAMESCENE_H__