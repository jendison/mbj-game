//auto create by tocpp.rb, plz don't modify it!
//2013-10-23 14:19:45 +0800
#include <string>
#include "cocos-ext.h"
#include "TypeDefine.h"
#include "TemplateBase.h"

#ifndef _TEMPLATECOMMON_H__
#define _TEMPLATECOMMON_H__
using std::string;
enum TCostType
{
TCostType_res = 0, //资源
TCostType_num = 1, //数值
TCostType_Cnt
};
enum TBuffTarget
{
TBuffTarget_selft = 0, //己方
TBuffTarget_enemy = 1, //敌方
TBuffTarget_all = 2, //全体
TBuffTarget_Cnt
};
enum TBuffType
{
TBuffType_buff = 0, //增益
TBuffType_debuff = 1, //减益
TBuffType_Cnt
};
enum TBuffEffect
{
TBuffEffect_speed = 0, //速度
TBuffEffect_skill = 1, //技能
TBuffEffect_Cnt
};
enum TNumberType
{
TNumberType_num = 0, //数值
TNumberType_percent = 1, //百分比(万进制)
TNumberType_Cnt
};
enum TSkillEffectType
{
TSkillEffectType_cast = 0, //施展
TSkillEffectType_trajectory = 1, //弹道
TSkillEffectType_hit = 2, //击中
TSkillEffectType_Cnt
};
enum TArmType
{
TArmType_land = 0, //地面
TArmType_sky = 1, //空中
TArmType_Cnt
};
enum TBool
{
TBool_false = 0, //false
TBool_true = 1, //true
TBool_Cnt
};
enum TAimMoveType
{
TAimMoveType_floor = 0, //地面
TAimMoveType_sky = 1, //飞行
TAimMoveType_Cnt
};


class TemplateCommon : public TemplateBase
{
public:
	TemplateCommon();
	~TemplateCommon(){}
	
	bool ReadJsonImpl(const CSJson::Value& obj);
	int32t getSNImpl() {return m_sn;}
	
public:

	
private:
	//sn
	int32t m_sn;

};

#endif //_TEMPLATECOMMON_H__
