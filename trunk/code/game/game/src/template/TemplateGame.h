//auto create by tocpp.rb, plz don't modify it!
//2013-08-24 16:53:27 +0800
#include <string>
#include "cocos-ext.h"
#include "TemplateCommon.h"
#include "TypeDefine.h"
#include "TemplateBase.h"

#ifndef _TEMPLATEGAME_H__
#define _TEMPLATEGAME_H__
using std::string;


class TemplateGame : public TemplateBase
{
public:
	TemplateGame();
	~TemplateGame(){}
	
	bool ReadJsonImpl(const CSJson::Value& obj);
	int32t getSNImpl() {return m_sn;}
	
public:
	int32t getAcamp() const{ return m_ACamp;}
	int32t getBcamp() const{ return m_BCamp;}
	int32t getResincspeed() const{ return m_resIncSpeed;}
	int32t getInitscene() const{ return m_initScene;}

	
private:
	//
	int32t m_sn;
	//A阵营
	int32t m_ACamp;
	//B阵营
	int32t m_BCamp;
	//每秒增长的资源数
	int32t m_resIncSpeed;
	//初始场景
	int32t m_initScene;

};

#endif //_TEMPLATEGAME_H__
