//auto create by tocpp.rb, plz don't modify it!
//2013-10-29 17:16:20 +0800
#include <string>
#include "cocos-ext.h"
#include "TemplateCommon.h"
#include "TypeDefine.h"
#include "TemplateBase.h"

#ifndef _TEMPLATEARMS_H__
#define _TEMPLATEARMS_H__
using std::string;
enum TDropType
{
TDropType_res = 0, //资源
TDropType_energy = 1, //能量
TDropType_moeny = 2, //金钱
TDropType_Cnt
};

struct SDropGroupItem:public TemplateBase
{
	SDropGroupItem()
	{
		rate = 0;
	num = 0;
	}
	//掉落类型
	TDropType dropType;
	//概率:0~1，小数
	float rate;
	//具体数值
	int32t num;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//掉落类型
	 getJsonVal(obj["dropType"], (int&)dropType); 
		//概率:0~1，小数
	 getJsonVal(obj["rate"], rate); 
		//具体数值
	 getJsonVal(obj["num"], num); 
		return true;
	}
};

class TemplateArms : public TemplateBase
{
public:
	TemplateArms();
	~TemplateArms(){}
	
	bool ReadJsonImpl(const CSJson::Value& obj);
	int32t getSNImpl() {return m_sn;}
	
public:
	const std::string& getShowname() const{ return m_ShowName;}
	const std::string& getAnimatepath() const{ return m_AnimatePath;}
	TAimMoveType getMovetype() const{ return m_MoveType;}
	int32t getAttack() const{ return m_Attack;}
	int32t getDefence() const{ return m_Defence;}
	int32t getHp() const{ return m_HP;}
	int32t getCd() const{ return m_CD;}
	int32t getSpeed() const{ return m_Speed;}
	TArmType getArmtype() const{ return m_ArmType;}
	TCostType getCosttype() const{ return m_CostType;}
	int32t getCostnum() const{ return m_CostNum;}
	int32t getAiconfig() const{ return m_AIConfig;}
	const vector<int32t>& getActiveskill() const{ return m_ActiveSkill;}
	const vector<int32t>& getPassiveskill() const{ return m_PassiveSkill;}
	int32t getBossskill() const{ return m_BossSkill;}
	const vector<SDropGroupItem>& getDropgroup() const{ return m_DropGroup;}

	
private:
	//sn
	int32t m_sn;
	//游戏里显示在UI的召唤对应兵种的面板上
	std::string m_ShowName;
	//对应的动画目录， 只需文件夹名即可
	std::string m_AnimatePath;
	//行走类型， 地面或者飞行
	TAimMoveType m_MoveType;
	//INT、兵种的生命上限
	int32t m_Attack;
	//INT、兵种的生命上限
	int32t m_Defence;
	//INT、兵种的生命上限
	int32t m_HP;
	//cd
	int32t m_CD;
	//速度，像素？INT
	int32t m_Speed;
	//兵种的类型，陆地的或者空中的
	TArmType m_ArmType;
	//资源、杀气
	TCostType m_CostType;
	//INT、对应上面的资源类型生效
	int32t m_CostNum;
	//INT、对应上面的资源类型生效
	int32t m_AIConfig;
	//选入技能模板，或者填ID
	vector<int32t> m_ActiveSkill;
	//选入技能模板，或者填ID
	vector<int32t> m_PassiveSkill;
	//选入技能模板，或者填ID
	int32t m_BossSkill;
	//掉落相关
	vector<SDropGroupItem> m_DropGroup;

};

#endif //_TEMPLATEARMS_H__
