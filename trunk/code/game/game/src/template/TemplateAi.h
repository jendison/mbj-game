//auto create by tocpp.rb, plz don't modify it!
//2013-10-29 17:14:26 +0800
#include <string>
#include "cocos-ext.h"
#include "TemplateCommon.h"
#include "TypeDefine.h"
#include "TemplateBase.h"

#ifndef _TEMPLATEAI_H__
#define _TEMPLATEAI_H__
using std::string;
enum TAIOpenType
{
TAIOpenType_afterBirthTime = 0, //出生后若干秒
TAIOpenType_HPPecent = 1, //HP百分比
TAIOpenType_Cnt
};

struct SAIConfig:public TemplateBase
{
	SAIConfig()
	{
		number = 0;
	loopTime = 0;
	}
	//开启方式
	TAIOpenType type;
	//开启数值
	int32t number;
	//优先级低于技能CD，即数值低于技能CD数值，则周期不生效
	int32t loopTime;
	//兵种模板里未填写的技能则不会被调用
	int32t skill;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//开启方式
	 getJsonVal(obj["type"], (int&)type); 
		//开启数值
	 getJsonVal(obj["number"], number); 
		//优先级低于技能CD，即数值低于技能CD数值，则周期不生效
	 getJsonVal(obj["loopTime"], loopTime); 
		//兵种模板里未填写的技能则不会被调用
	 getJsonVal(obj["skill"], skill); 
		return true;
	}
};

class TemplateAi : public TemplateBase
{
public:
	TemplateAi();
	~TemplateAi(){}
	
	bool ReadJsonImpl(const CSJson::Value& obj);
	int32t getSNImpl() {return m_sn;}
	
public:
	const std::string& getShowname() const{ return m_ShowName;}
	const vector<SAIConfig>& getAiconfig() const{ return m_AIConfig;}

	
private:
	//
	int32t m_sn;
	//AI名字
	std::string m_ShowName;
	//AI配置
	vector<SAIConfig> m_AIConfig;

};

#endif //_TEMPLATEAI_H__
