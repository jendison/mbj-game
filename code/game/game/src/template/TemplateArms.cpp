//auto create by tocpp.rb, plz don't modify it!
//2013-10-29 17:16:20 +0800

#include "TemplateArms.h"

using std::string;

TemplateArms::TemplateArms()
{
	m_sn = 0;
	m_Attack = 0;
	m_Defence = 0;
	m_HP = 0;
	m_CD = 0;
	m_Speed = 0;
	m_CostType =(TCostType) 1;
	m_CostNum = 0;
	m_AIConfig = 0;
//
}

bool TemplateArms::ReadJsonImpl(const CSJson::Value& obj)
{
		//sn
	 getJsonVal(obj["sn"], m_sn); 
		//游戏里显示在UI的召唤对应兵种的面板上
	 getJsonVal(obj["ShowName"], m_ShowName); 
		//对应的动画目录， 只需文件夹名即可
	 getJsonVal(obj["AnimatePath"], m_AnimatePath); 
		//行走类型， 地面或者飞行
	 getJsonVal(obj["MoveType"], (int&)m_MoveType); 
		//INT、兵种的生命上限
	 getJsonVal(obj["Attack"], m_Attack); 
		//INT、兵种的生命上限
	 getJsonVal(obj["Defence"], m_Defence); 
		//INT、兵种的生命上限
	 getJsonVal(obj["HP"], m_HP); 
		//cd
	 getJsonVal(obj["CD"], m_CD); 
		//速度，像素？INT
	 getJsonVal(obj["Speed"], m_Speed); 
		//兵种的类型，陆地的或者空中的
	 getJsonVal(obj["ArmType"], (int&)m_ArmType); 
		//资源、杀气
	 getJsonVal(obj["CostType"], (int&)m_CostType); 
		//INT、对应上面的资源类型生效
	 getJsonVal(obj["CostNum"], m_CostNum); 
		//INT、对应上面的资源类型生效
	 getJsonVal(obj["AIConfig"], m_AIConfig); 
		//选入技能模板，或者填ID
	 getJsonVal(obj["ActiveSkill"], m_ActiveSkill); 
		//选入技能模板，或者填ID
	 getJsonVal(obj["PassiveSkill"], m_PassiveSkill); 
		//选入技能模板，或者填ID
	 getJsonVal(obj["BossSkill"], m_BossSkill); 

				//掉落相关
	
		 const CSJson::Value& tmp = obj["DropGroup"];
		uint32t nSize = tmp.size();
		for (uint32t i = 0; i < nSize; ++i)
		{
			SDropGroupItem n;
			n.ReadJsonImpl(tmp[i]);
			m_DropGroup.push_back(n);
		}		
		
	return true;
}



