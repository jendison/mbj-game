#include "TemplateBase.h"

void TemplateBase::getJsonVal( const CSJson::Value& obj, int32t& val )
{
	if (!obj.isNull())
	{
		if (obj.type() == CSJson::intValue)
		{
			val = obj.asInt();
		}
		else if (obj.type() == CSJson::stringValue)
		{
			const char* pStr = obj.asCString();
			val = atoi(pStr);		
		}

	}
}

void TemplateBase::getJsonVal( const CSJson::Value& obj, std::string& val )
{
	if (!obj.isNull())
	{
		const char* pStr = obj.asCString();
		val = pStr;
	}
}

void TemplateBase::getJsonVal( const CSJson::Value& obj, bool& val )
{
	if (!obj.isNull())
	{
		const char* pStr = obj.asCString();
		val = (bool)atoi(pStr);
	}

}

void TemplateBase::getJsonVal( const CSJson::Value& obj, vector<int>& val )
{
	if (!obj.isNull())
	{
		uint32t nSize = obj.size();
		for (uint32t i = 0; i < nSize; ++i)
		{
			int n = 0;
			getJsonVal(obj[i], n);
			val.push_back(n);
		}
	}
}

void TemplateBase::getJsonVal( const CSJson::Value& obj, float& val )
{
	if (!obj.isNull())
	{
		if (obj.type() == CSJson::realValue)
		{
			val = obj.asFloat();
		}
		else if (obj.type() == CSJson::stringValue)
		{
			const char* pStr = obj.asCString();
			val = atof(pStr);		
		}
	}
}
