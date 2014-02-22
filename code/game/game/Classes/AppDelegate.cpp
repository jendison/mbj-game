#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"

#include <vector>
#include <string>

#include "GameBattleLayer.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"
#include "LuaHelper.h"

#include "../logic/WelcomeScene.h"
#include "../logic/GameWorld.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::extension;
using namespace CocosDenshion;
AppDelegate::AppDelegate() : m_pGameWorld(NULL), m_pLuaHelper(NULL)
{

}

AppDelegate::~AppDelegate() 
{
	m_pGameWorld->Stop();

	CC_SAFE_DELETE(m_pGameWorld);

	CC_SAFE_DELETE(m_pLuaHelper);
	SceneReader::purge();
	ActionManager::purge();
	GUIReader::purge();
	CCArmatureDataManager::purge();
	CCDataReaderHelper::purge();
	ObjectFactory::getInstance()->destroyInstance();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	if (m_pGameWorld == NULL)
	{
		m_pGameWorld = new GameWorld();
	}

	if (m_pLuaHelper == NULL)
	{
		m_pLuaHelper = new LuaHelper();
	}
	

	GAME_ASSERT_RET(m_pGameWorld, false, ("new fail"));

	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	int nWidth = CCUserDefault::sharedUserDefault()->getIntegerForKey("width", 0);
	int nHeight = CCUserDefault::sharedUserDefault()->getIntegerForKey("height", 0);
	if (nHeight == 0 || nWidth == 0)
	{
		CCSize size = CCEGLView::sharedOpenGLView()->getFrameSize();
		nWidth = size.width;
		nHeight = size.height;
		CCUserDefault::sharedUserDefault()->setIntegerForKey("width", nWidth);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("height", nHeight);
	}

	pEGLView->setFrameSize(nWidth,nHeight);
	pDirector->setOpenGLView(pEGLView);

	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(960,640, kResolutionNoBorder);

	CCSize frameSize = pEGLView->getFrameSize();


	vector<string> searchPath;
    //searchPath.push_back("Resources");
	m_pLuaHelper->init();

	//预加载纹理
	CCTextureCache::sharedTextureCache()->addImage("sprite.png");	

	//创建绘制批处理节点
	//这里的精灵帧缓存添加第二个参数实际上是使用了预加载的纹理缓存中的图片
	//也就是说第二个参数可以说是 CCTexture2D而不是单纯的textureFileName
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprite.plist","sprite.png");

	// In this demo, we select resource according to the frame's height.
	// If the resource size is different from design resolution size, you need to set contentScaleFactor.
	// We use the ratio of resource's height to the height of design resolution,
	// this can make sure that the resource's height could fit for the height of design resolution.

	//// if the frame's height is larger than the height of medium resource size, select large resource.
	//if (frameSize.height > mediumResource.size.height)
	//{
	//	searchPath.push_back(largeResource.directory);

	//	pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	//}
	//// if the frame's height is larger than the height of small resource size, select medium resource.
	//else if (frameSize.height > smallResource.size.height)
	//{
	//	searchPath.push_back(mediumResource.directory);

	//	pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
	//}
	//// if the frame's height is smaller than the height of medium resource size, select small resource.
	//else
	//{
	//	searchPath.push_back(smallResource.directory);

	//	pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
	//}

	// set searching path
	//CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

	// turn on display FPS
	pDirector->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);
	WelcomeScene* pScene = WelcomeScene::create();
	GAME_ASSERT_RET(pScene, false, ("welcomet gui invalid"));
	pDirector->runWithScene(pScene);
	//m_pGameWorld->Init();
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
