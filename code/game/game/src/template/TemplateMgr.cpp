#include "TemplateMgr.h"
#include "TemplateScene.h"
#include "TemplateBase.h"
#include "TemplateGame.h"
#include "Macro.h"
#include <../CCFileUtils.h>
using namespace cocos2d;

const char* g_pDataZipFileName = "data.zip";
TemplateMgr::TemplateMgr()
{

}

TemplateMgr::~TemplateMgr()
{
	for (TTemplateList::iterator itr = m_objectList.begin(); itr != m_objectList.end(); ++itr)
	{
		delete itr->second;
		itr->second = NULL;
	}
	m_objectList.clear();
}



bool TemplateMgr::Init()
{
	return true;
}

bool TemplateMgr::getJsonFormZipFile( const char* pStrfileName, CSJson::Value& outJson )
{
	unsigned long lSize;

	unsigned char* pFile = CCFileUtils::sharedFileUtils()->getFileData(pStrfileName, "r", &lSize);
	GAME_ASSERT_RET(pFile, false, ( "read data file fail"));

	CSJson::Reader rd;
	if (!rd.parse(string((const char*)pFile, (string::size_type)lSize), outJson))
	{
		delete pFile;
		pFile = NULL;
		return false;
	}

	delete pFile;
	pFile = NULL;
	return true;
}


