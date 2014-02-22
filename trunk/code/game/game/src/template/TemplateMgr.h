#include <string>
#include <map>

#include "support/zip_support/ZipUtils.h"
#include "CocoStudio/Json/lib_json/json_lib.h"
#include "TypeDefine.h"
#include "Macro.h"

#ifndef __TEMPLATEMGR_H__
#define __TEMPLATEMGR_H__

class TemplateBase;
using std::map;
using std::string;
typedef map<int32t, TemplateBase*> TTemplateList;

class TemplateMgr
{
public:
	TemplateMgr();
	~TemplateMgr();
	bool Init();

	template <class T>
	const T* get( int32t nSN )
	{
		TTemplateList::iterator itr = m_objectList.find(nSN);

		if (itr != m_objectList.end())
		{
			TemplateBase* p = itr->second;
			T* pRet = dynamic_cast<T*>(p);
			GAME_ASSERT_RET(pRet, NULL, ("template mgr get sn fail, invalid type"));
			return pRet;
		}

		//合成名字 xxx.js
		char fileName[128] = {0};
		sprintf(fileName, "data/%d.js", nSN);
		CSJson::Value obj;
		GAME_ASSERT_RET(getJsonFormZipFile(fileName, obj), NULL, ( "get data from zip fail"));

		//生成对象
		T* p = new T;
		GAME_ASSERT_RET(p, NULL, ( "new fail"));
		if (!p->readJson(obj))
		{
			delete p;
			p = NULL;
			return NULL;
		}
		//插入成列表
		m_objectList.insert(std::make_pair(p->getSN(), p));
		return p;
	}

private:
	bool getJsonFormZipFile(const char* pStrfileName, CSJson::Value& outJson);

private:
	TTemplateList m_objectList;
};

#endif // !__TEMPLATEMGR_H__
