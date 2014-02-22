//auto create by tocpp.rb, plz don't modify it!
//2013-10-29 17:14:25 +0800
#include <string>
#include "cocos-ext.h"
#include "TemplateCommon.h"
#include "TypeDefine.h"
#include "TemplateBase.h"

#ifndef _TEMPLATESKILL_H__
#define _TEMPLATESKILL_H__
using std::string;
enum TAOEType
{
TAOEType_line = 0, //直线
TAOEType_sector = 1, //扇形
TAOEType_Cnt
};

struct SkillEffect:public TemplateBase
{
	SkillEffect()
	{
		}
	//光效类型
	TSkillEffectType skillEffectType;
	//光效类型
	std::string skillEffectPath;
	//光效类型
	std::string skillSoundPath;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//光效类型
	 getJsonVal(obj["skillEffectType"], (int&)skillEffectType); 
		//光效类型
	 getJsonVal(obj["skillEffectPath"], skillEffectPath); 
		//光效类型
	 getJsonVal(obj["skillSoundPath"], skillSoundPath); 
		return true;
	}
};
struct AOELine:public TemplateBase
{
	AOELine()
	{
		}
	//光效类型
	float height;
	//光效类型
	float width;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//光效类型
	 getJsonVal(obj["height"], height); 
		//光效类型
	 getJsonVal(obj["width"], width); 
		return true;
	}
};
struct AOESector:public TemplateBase
{
	AOESector()
	{
		MinAngle = 0;
	MaxAngle = 0;
	Radio = 0;
	}
	//最小角度
	float MinAngle;
	//最大角度
	float MaxAngle;
	//扇形半径
	float Radio;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//最小角度
	 getJsonVal(obj["MinAngle"], MinAngle); 
		//最大角度
	 getJsonVal(obj["MaxAngle"], MaxAngle); 
		//扇形半径
	 getJsonVal(obj["Radio"], Radio); 
		return true;
	}
};
struct SkillUpLevelInfo:public TemplateBase
{
	SkillUpLevelInfo()
	{
		NeedGameMoney = 0;
	}
	//下一级技能
	int32t NextSkillObject;
	//升级所需金钱
	int32t NeedGameMoney;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//下一级技能
	 getJsonVal(obj["NextSkillObject"], NextSkillObject); 
		//升级所需金钱
	 getJsonVal(obj["NeedGameMoney"], NeedGameMoney); 
		return true;
	}
};

class TemplateSkill : public TemplateBase
{
public:
	TemplateSkill();
	~TemplateSkill(){}
	
	bool ReadJsonImpl(const CSJson::Value& obj);
	int32t getSNImpl() {return m_sn;}
	
public:
	const std::string& getShowname() const{ return m_ShowName;}
	int32t getDistance() const{ return m_Distance;}
	TBool getIsautoplay() const{ return m_IsAutoPlay;}
	int32t getSkillcd() const{ return m_SkillCD;}
	int32t getTrajectoryspeed() const{ return m_TrajectorySpeed;}
	const std::string& getScriptfunc() const{ return m_scriptFunc;}
	const SkillUpLevelInfo& getUplevelsetting() const{ return m_UpLevelSetting;}
	TAOEType getAoetype() const{ return m_AOEType;}
	int32t getStartplayskilleffecttime() const{ return m_StartPlaySkillEffectTime;}
	const AOELine& getLinesetting() const{ return m_LineSetting;}
	const AOESector& getSectorsetting() const{ return m_SectorSetting;}
	const vector<SkillEffect>& getEffectres() const{ return m_effectRes;}

	
private:
	//sn
	int32t m_sn;
	//显示名
	std::string m_ShowName;
	//施法距离
	int32t m_Distance;
	//是否自动播放
	TBool m_IsAutoPlay;
	//技能CD
	int32t m_SkillCD;
	//弹道特效的移动速度
	int32t m_TrajectorySpeed;
	//造成伤害的脚本函数
	std::string m_scriptFunc;
	//技能升级设定
	SkillUpLevelInfo m_UpLevelSetting;
	//AOE判定范围类型
	TAOEType m_AOEType;
	//这个时间结束开始播放弹道或者AOE特效
	int32t m_StartPlaySkillEffectTime;
	//AOE判定范围类型-直线
	AOELine m_LineSetting;
	//AOE判定范围类型扇形，以人物朝向逆时针为正方向，范围为[-180,180]
	AOESector m_SectorSetting;
	//特效资源
	vector<SkillEffect> m_effectRes;

};

#endif //_TEMPLATESKILL_H__
