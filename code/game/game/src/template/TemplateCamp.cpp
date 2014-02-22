//auto create by tocpp.rb, plz don't modify it!
//2013-08-24 16:53:27 +0800

#include "TemplateCamp.h"

using std::string;

TemplateCamp::TemplateCamp()
{
	m_sn = 0;
	m_InitResouce = 0;
	m_ResouceIncCD = 0;
	m_ResouceIncNum = 0;
	m_IsRebot = 0;

}

bool TemplateCamp::ReadJsonImpl(const CSJson::Value& obj)
{
		//sn
	 getJsonVal(obj["sn"], m_sn); 
		//显示名
	 getJsonVal(obj["ShowName"], m_ShowName); 
		//核心兵种
	 getJsonVal(obj["CoreArm"], m_CoreArm); 
		//初始资源数量
	 getJsonVal(obj["InitResouce"], m_InitResouce); 
		//资源的增长cd
	 getJsonVal(obj["ResouceIncCD"], m_ResouceIncCD); 
		//资源的增长数值
	 getJsonVal(obj["ResouceIncNum"], m_ResouceIncNum); 
		//是否机器人
	 getJsonVal(obj["IsRebot"], m_IsRebot); 
		//初始建筑列表
	 getJsonVal(obj["InitBuilding"], m_InitBuilding); 

	return true;
}



