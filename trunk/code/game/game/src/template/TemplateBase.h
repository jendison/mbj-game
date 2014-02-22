#include "cocos-ext.h"
#include "TypeDefine.h"
#include <string>
#include <vector>
#include "CocoStudio/Json/lib_json/json_lib.h"

#ifndef __TEMPLATEBASE_H__
#define __TEMPLATEBASE_H__

using std::vector;

class TemplateBase
{
public:
	virtual ~TemplateBase(){}
	bool readJson(const CSJson::Value& obj)
	{
		return ReadJsonImpl(obj);
	}
	int32t getSN()
	{
		return getSNImpl();
	}

protected:
	virtual int32t getSNImpl(){return 0;};
	virtual bool ReadJsonImpl(const CSJson::Value& obj) = 0;
	void	getJsonVal(const CSJson::Value& obj, int32t& val);
	void	getJsonVal(const CSJson::Value& obj, std::string& val);
	void	getJsonVal(const CSJson::Value& obj, bool& val);
	void	getJsonVal(const CSJson::Value& obj, vector<int>& val);
	void	getJsonVal(const CSJson::Value& obj, float& val);
};


#endif//__TEMPLATEBASE_H__