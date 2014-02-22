//auto create by tocpp.rb, plz don't modify it!
//2013-10-23 14:19:45 +0800

#include "TemplateHero.h"

using std::string;

TemplateHero::TemplateHero()
{
	m_sn = 0;
	m_LevelUpIncAttack = 0;
	m_LevelUpIncDefence = 0;
	m_LevelUpIncHP = 0;
	m_LevelUpIncEnergy = 0;

}

bool TemplateHero::ReadJsonImpl(const CSJson::Value& obj)
{
		//
	 getJsonVal(obj["sn"], m_sn); 
		//引用的兵种模版
	 getJsonVal(obj["Arm"], m_Arm); 
		//英雄的品质
	 getJsonVal(obj["Quality"], (int&)m_Quality); 
		//升级后提升攻击
	 getJsonVal(obj["LevelUpIncAttack"], m_LevelUpIncAttack); 
		//升级后提升防御
	 getJsonVal(obj["LevelUpIncDefence"], m_LevelUpIncDefence); 
		//升级后提升HP
	 getJsonVal(obj["LevelUpIncHP"], m_LevelUpIncHP); 
		//升级后提升能量
	 getJsonVal(obj["LevelUpIncEnergy"], m_LevelUpIncEnergy); 

	return true;
}



