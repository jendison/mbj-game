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
	//��Դ��ɱ����2ѡ1
	TCostType CostType;
	//INT����Ӧ�������Դ������Ч
	int32t CostNum;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//��Դ��ɱ����2ѡ1
	 getJsonVal(obj["CostType"], (int&)CostType); 
		//INT����Ӧ�������Դ������Ч
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
	//��Ϸ����ʾ��UI�Ľ����Ӧ�����������
	std::string m_ShowName;
	//������ť��ͼ��
	std::string m_icon;
	//��Ӧ��������
	int32t m_Arms;
	//����
	SCost m_Cost;

};

#endif //_TEMPLATEBUILDING_H__
