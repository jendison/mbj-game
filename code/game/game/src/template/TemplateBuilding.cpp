//auto create by tocpp.rb, plz don't modify it!
//2013-08-24 16:53:26 +0800

#include "TemplateBuilding.h"

using std::string;

TemplateBuilding::TemplateBuilding()
{
	m_sn = 0;
//
}

bool TemplateBuilding::ReadJsonImpl(const CSJson::Value& obj)
{
		//sn
	 getJsonVal(obj["sn"], m_sn); 
		//游戏里显示在UI的建造对应建筑的面板上
	 getJsonVal(obj["ShowName"], m_ShowName); 
		//建筑按钮的图标
	 getJsonVal(obj["icon"], m_icon); 
		//对应产生兵种
	 getJsonVal(obj["Arms"], m_Arms); 
		//消耗
	 m_Cost.ReadJsonImpl(obj["Cost"]); 

	return true;
}



