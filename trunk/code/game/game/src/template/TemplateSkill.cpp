//auto create by tocpp.rb, plz don't modify it!
//2013-10-29 17:14:25 +0800

#include "TemplateSkill.h"

using std::string;

TemplateSkill::TemplateSkill()
{
	m_sn = 0;
	m_Distance = 0;
	m_SkillCD = 0;
	m_TrajectorySpeed = 0;
	m_scriptFunc = "20";
////////
}

bool TemplateSkill::ReadJsonImpl(const CSJson::Value& obj)
{
		//sn
	 getJsonVal(obj["sn"], m_sn); 
		//显示名
	 getJsonVal(obj["ShowName"], m_ShowName); 
		//施法距离
	 getJsonVal(obj["Distance"], m_Distance); 
		//是否自动播放
	 getJsonVal(obj["IsAutoPlay"], (int&)m_IsAutoPlay); 
		//技能CD
	 getJsonVal(obj["SkillCD"], m_SkillCD); 
		//弹道特效的移动速度
	 getJsonVal(obj["TrajectorySpeed"], m_TrajectorySpeed); 
		//造成伤害的脚本函数
	 getJsonVal(obj["scriptFunc"], m_scriptFunc); 
		//技能升级设定
	 m_UpLevelSetting.ReadJsonImpl(obj["UpLevelSetting"]); 
		//AOE判定范围类型
	 getJsonVal(obj["AOEType"], (int&)m_AOEType); 
		//这个时间结束开始播放弹道或者AOE特效
	 getJsonVal(obj["StartPlaySkillEffectTime"], m_StartPlaySkillEffectTime); 
		//AOE判定范围类型-直线
	 m_LineSetting.ReadJsonImpl(obj["LineSetting"]); 
		//AOE判定范围类型扇形，以人物朝向逆时针为正方向，范围为[-180,180]
	 m_SectorSetting.ReadJsonImpl(obj["SectorSetting"]); 

				//特效资源
	
		 const CSJson::Value& tmp = obj["effectRes"];
		uint32t nSize = tmp.size();
		for (uint32t i = 0; i < nSize; ++i)
		{
			SkillEffect n;
			n.ReadJsonImpl(tmp[i]);
			m_effectRes.push_back(n);
		}		
		
	return true;
}



