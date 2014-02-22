//auto create by tocpp.rb, plz don't modify it!
//2013-08-24 16:53:27 +0800
#include <string>
#include "cocos-ext.h"
#include "TemplateCommon.h"
#include "TypeDefine.h"
#include "TemplateBase.h"

#ifndef _TEMPLATECAMP_H__
#define _TEMPLATECAMP_H__
using std::string;


class TemplateCamp : public TemplateBase
{
public:
	TemplateCamp();
	~TemplateCamp(){}
	
	bool ReadJsonImpl(const CSJson::Value& obj);
	int32t getSNImpl() {return m_sn;}
	
public:
	const std::string& getShowname() const{ return m_ShowName;}
	int32t getCorearm() const{ return m_CoreArm;}
	int32t getInitresouce() const{ return m_InitResouce;}
	int32t getResouceinccd() const{ return m_ResouceIncCD;}
	int32t getResouceincnum() const{ return m_ResouceIncNum;}
	int32t getIsrebot() const{ return m_IsRebot;}
	const vector<int32t>& getInitbuilding() const{ return m_InitBuilding;}

	
private:
	//sn
	int32t m_sn;
	//显示名
	std::string m_ShowName;
	//核心兵种
	int32t m_CoreArm;
	//初始资源数量
	int32t m_InitResouce;
	//资源的增长cd
	int32t m_ResouceIncCD;
	//资源的增长数值
	int32t m_ResouceIncNum;
	//是否机器人
	int32t m_IsRebot;
	//初始建筑列表
	vector<int32t> m_InitBuilding;

};

#endif //_TEMPLATECAMP_H__
