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
TAIOpenType_afterBirthTime = 0, //������������
TAIOpenType_HPPecent = 1, //HP�ٷֱ�
TAIOpenType_Cnt
};

struct SAIConfig:public TemplateBase
{
	SAIConfig()
	{
		number = 0;
	loopTime = 0;
	}
	//������ʽ
	TAIOpenType type;
	//������ֵ
	int32t number;
	//���ȼ����ڼ���CD������ֵ���ڼ���CD��ֵ�������ڲ���Ч
	int32t loopTime;
	//����ģ����δ��д�ļ����򲻻ᱻ����
	int32t skill;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//������ʽ
	 getJsonVal(obj["type"], (int&)type); 
		//������ֵ
	 getJsonVal(obj["number"], number); 
		//���ȼ����ڼ���CD������ֵ���ڼ���CD��ֵ�������ڲ���Ч
	 getJsonVal(obj["loopTime"], loopTime); 
		//����ģ����δ��д�ļ����򲻻ᱻ����
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
	//AI����
	std::string m_ShowName;
	//AI����
	vector<SAIConfig> m_AIConfig;

};

#endif //_TEMPLATEAI_H__
