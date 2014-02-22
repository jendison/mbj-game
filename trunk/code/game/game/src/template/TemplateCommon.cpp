//auto create by tocpp.rb, plz don't modify it!
//2013-10-23 14:19:45 +0800

#include "TemplateCommon.h"

using std::string;

TemplateCommon::TemplateCommon()
{
	m_sn = 0;

}

bool TemplateCommon::ReadJsonImpl(const CSJson::Value& obj)
{
		//sn
	 getJsonVal(obj["sn"], m_sn); 

	return true;
}



