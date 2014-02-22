//auto create by tocpp.rb, plz don't modify it!
//2013-10-29 17:14:26 +0800

#include "TemplateAi.h"

using std::string;

TemplateAi::TemplateAi()
{
	m_sn = 0;
//
}

bool TemplateAi::ReadJsonImpl(const CSJson::Value& obj)
{
		//
	 getJsonVal(obj["sn"], m_sn); 
		//AI√˚◊÷
	 getJsonVal(obj["ShowName"], m_ShowName); 

				//AI≈‰÷√
	
		 const CSJson::Value& tmp = obj["AIConfig"];
		uint32t nSize = tmp.size();
		for (uint32t i = 0; i < nSize; ++i)
		{
			SAIConfig n;
			n.ReadJsonImpl(tmp[i]);
			m_AIConfig.push_back(n);
		}		
		
	return true;
}



