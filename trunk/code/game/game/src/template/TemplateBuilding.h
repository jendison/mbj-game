//auto create by tocpp.rb, plz don't modify it!
//2013-08-24 16:53:26 +0800
#include <string>
#include "cocos-ext.h"
#include "TemplateCommon.h"
#include "TypeDefine.h"
#include "TemplateBase.h"

#ifndef _TEMPLATEBUILDING_H__
#define _TEMPLATEBUILDING_H__
using std::string;

struct SCost:public TemplateBase
{
	SCost()
	{
		CostType =(TCostType) 1;
	CostNum = 0;
	}
	//资源、杀气。2选1
	TCostType CostType;
	//INT、对应上面的资源类型生效
	int32t CostNum;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//资源、杀气。2选1
	 getJsonVal(obj["CostType"], (int&)CostType); 
		//INT、对应上面的资源类型生效
	 getJsonVal(obj["CostNum"], CostNum); 
		return true;
	}
};

class TemplateBuilding : public TemplateBase
{
public:
	TemplateBuilding();
	~TemplateBuilding(){}
	
	bool ReadJsonImpl(const CSJson::Value& obj);
	int32t getSNImpl() {return m_sn;}
	
public:
	const std::string& getShowname() const{ return m_ShowName;}
	const std::string& getIcon() const{ return m_icon;}
	int32t getArms() const{ return m_Arms;}
	const SCost& getCost() const{ return m_Cost;}

	
private:
	//sn
	int32t m_sn;
	//游戏里显示在UI的建造对应建筑的面板上
	std::string m_ShowName;
	//建筑按钮的图标
	std::string m_icon;
	//对应产生兵种
	int32t m_Arms;
	//消耗
	SCost m_Cost;

};

#endif //_TEMPLATEBUILDING_H__
