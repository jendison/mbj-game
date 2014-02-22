//auto create by tocpp.rb, plz don't modify it!
//2013-08-24 16:53:27 +0800

#include "TemplateGame.h"

using std::string;

TemplateGame::TemplateGame()
{
	m_sn = 0;

}

bool TemplateGame::ReadJsonImpl(const CSJson::Value& obj)
{
		//
	 getJsonVal(obj["sn"], m_sn); 
		//A阵营
	 getJsonVal(obj["ACamp"], m_ACamp); 
		//B阵营
	 getJsonVal(obj["BCamp"], m_BCamp); 
		//每秒增长的资源数
	 getJsonVal(obj["resIncSpeed"], m_resIncSpeed); 
		//初始场景
	 getJsonVal(obj["initScene"], m_initScene); 

	return true;
}



