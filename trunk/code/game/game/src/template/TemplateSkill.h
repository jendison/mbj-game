//auto create by tocpp.rb, plz don't modify it!
//2013-10-29 17:14:25 +0800
#include <string>
#include "cocos-ext.h"
#include "TemplateCommon.h"
#include "TypeDefine.h"
#include "TemplateBase.h"

#ifndef _TEMPLATESKILL_H__
#define _TEMPLATESKILL_H__
using std::string;
enum TAOEType
{
TAOEType_line = 0, //ֱ��
TAOEType_sector = 1, //����
TAOEType_Cnt
};

struct SkillEffect:public TemplateBase
{
	SkillEffect()
	{
		}
	//��Ч����
	TSkillEffectType skillEffectType;
	//��Ч����
	std::string skillEffectPath;
	//��Ч����
	std::string skillSoundPath;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//��Ч����
	 getJsonVal(obj["skillEffectType"], (int&)skillEffectType); 
		//��Ч����
	 getJsonVal(obj["skillEffectPath"], skillEffectPath); 
		//��Ч����
	 getJsonVal(obj["skillSoundPath"], skillSoundPath); 
		return true;
	}
};
struct AOELine:public TemplateBase
{
	AOELine()
	{
		}
	//��Ч����
	float height;
	//��Ч����
	float width;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//��Ч����
	 getJsonVal(obj["height"], height); 
		//��Ч����
	 getJsonVal(obj["width"], width); 
		return true;
	}
};
struct AOESector:public TemplateBase
{
	AOESector()
	{
		MinAngle = 0;
	MaxAngle = 0;
	Radio = 0;
	}
	//��С�Ƕ�
	float MinAngle;
	//���Ƕ�
	float MaxAngle;
	//���ΰ뾶
	float Radio;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//��С�Ƕ�
	 getJsonVal(obj["MinAngle"], MinAngle); 
		//���Ƕ�
	 getJsonVal(obj["MaxAngle"], MaxAngle); 
		//���ΰ뾶
	 getJsonVal(obj["Radio"], Radio); 
		return true;
	}
};
struct SkillUpLevelInfo:public TemplateBase
{
	SkillUpLevelInfo()
	{
		NeedGameMoney = 0;
	}
	//��һ������
	int32t NextSkillObject;
	//���������Ǯ
	int32t NeedGameMoney;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//��һ������
	 getJsonVal(obj["NextSkillObject"], NextSkillObject); 
		//���������Ǯ
	 getJsonVal(obj["NeedGameMoney"], NeedGameMoney); 
		return true;
	}
};

class TemplateSkill : public TemplateBase
{
public:
	TemplateSkill();
	~TemplateSkill(){}
	
	bool ReadJsonImpl(const CSJson::Value& obj);
	int32t getSNImpl() {return m_sn;}
	
public:
	const std::string& getShowname() const{ return m_ShowName;}
	int32t getDistance() const{ return m_Distance;}
	TBool getIsautoplay() const{ return m_IsAutoPlay;}
	int32t getSkillcd() const{ return m_SkillCD;}
	int32t getTrajectoryspeed() const{ return m_TrajectorySpeed;}
	const std::string& getScriptfunc() const{ return m_scriptFunc;}
	const SkillUpLevelInfo& getUplevelsetting() const{ return m_UpLevelSetting;}
	TAOEType getAoetype() const{ return m_AOEType;}
	int32t getStartplayskilleffecttime() const{ return m_StartPlaySkillEffectTime;}
	const AOELine& getLinesetting() const{ return m_LineSetting;}
	const AOESector& getSectorsetting() const{ return m_SectorSetting;}
	const vector<SkillEffect>& getEffectres() const{ return m_effectRes;}

	
private:
	//sn
	int32t m_sn;
	//��ʾ��
	std::string m_ShowName;
	//ʩ������
	int32t m_Distance;
	//�Ƿ��Զ�����
	TBool m_IsAutoPlay;
	//����CD
	int32t m_SkillCD;
	//������Ч���ƶ��ٶ�
	int32t m_TrajectorySpeed;
	//����˺��Ľű�����
	std::string m_scriptFunc;
	//���������趨
	SkillUpLevelInfo m_UpLevelSetting;
	//AOE�ж���Χ����
	TAOEType m_AOEType;
	//���ʱ�������ʼ���ŵ�������AOE��Ч
	int32t m_StartPlaySkillEffectTime;
	//AOE�ж���Χ����-ֱ��
	AOELine m_LineSetting;
	//AOE�ж���Χ�������Σ������ﳯ����ʱ��Ϊ�����򣬷�ΧΪ[-180,180]
	AOESector m_SectorSetting;
	//��Ч��Դ
	vector<SkillEffect> m_effectRes;

};

#endif //_TEMPLATESKILL_H__
