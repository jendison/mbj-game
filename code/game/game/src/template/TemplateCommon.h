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
TCostType_res = 0, //��Դ
TCostType_num = 1, //��ֵ
TCostType_Cnt
};
enum TBuffTarget
{
TBuffTarget_selft = 0, //����
TBuffTarget_enemy = 1, //�з�
TBuffTarget_all = 2, //ȫ��
TBuffTarget_Cnt
};
enum TBuffType
{
TBuffType_buff = 0, //����
TBuffType_debuff = 1, //����
TBuffType_Cnt
};
enum TBuffEffect
{
TBuffEffect_speed = 0, //�ٶ�
TBuffEffect_skill = 1, //����
TBuffEffect_Cnt
};
enum TNumberType
{
TNumberType_num = 0, //��ֵ
TNumberType_percent = 1, //�ٷֱ�(�����)
TNumberType_Cnt
};
enum TSkillEffectType
{
TSkillEffectType_cast = 0, //ʩչ
TSkillEffectType_trajectory = 1, //����
TSkillEffectType_hit = 2, //����
TSkillEffectType_Cnt
};
enum TArmType
{
TArmType_land = 0, //����
TArmType_sky = 1, //����
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
TAimMoveType_floor = 0, //����
TAimMoveType_sky = 1, //����
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
