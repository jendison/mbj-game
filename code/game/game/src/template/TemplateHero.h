//auto create by tocpp.rb, plz don't modify it!
//2013-10-23 14:19:45 +0800
#include <string>
#include "cocos-ext.h"
#include "TemplateCommon.h"
#include "TypeDefine.h"
#include "TemplateBase.h"

#ifndef _TEMPLATEHERO_H__
#define _TEMPLATEHERO_H__
using std::string;
enum THeroQuality
{
THeroQuality_one = 0, //1
THeroQuality_two = 1, //2
THeroQuality_three = 2, //3
THeroQuality_four = 3, //4
THeroQuality_five = 4, //5
THeroQuality_Cnt
};


class TemplateHero : public TemplateBase
{
public:
	TemplateHero();
	~TemplateHero(){}
	
	bool ReadJsonImpl(const CSJson::Value& obj);
	int32t getSNImpl() {return m_sn;}
	
public:
	int32t getArm() const{ return m_Arm;}
	THeroQuality getQuality() const{ return m_Quality;}
	int32t getLevelupincattack() const{ return m_LevelUpIncAttack;}
	int32t getLevelupincdefence() const{ return m_LevelUpIncDefence;}
	int32t getLevelupinchp() const{ return m_LevelUpIncHP;}
	int32t getLevelupincenergy() const{ return m_LevelUpIncEnergy;}

	
private:
	//
	int32t m_sn;
	//引用的兵种模版
	int32t m_Arm;
	//英雄的品质
	THeroQuality m_Quality;
	//升级后提升攻击
	int32t m_LevelUpIncAttack;
	//升级后提升防御
	int32t m_LevelUpIncDefence;
	//升级后提升HP
	int32t m_LevelUpIncHP;
	//升级后提升能量
	int32t m_LevelUpIncEnergy;

};

#endif //_TEMPLATEHERO_H__
