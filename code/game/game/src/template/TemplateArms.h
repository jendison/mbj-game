//auto create by tocpp.rb, plz don't modify it!
//2013-10-29 17:16:20 +0800
#include <string>
#include "cocos-ext.h"
#include "TemplateCommon.h"
#include "TypeDefine.h"
#include "TemplateBase.h"

#ifndef _TEMPLATEARMS_H__
#define _TEMPLATEARMS_H__
using std::string;
enum TDropType
{
TDropType_res = 0, //��Դ
TDropType_energy = 1, //����
TDropType_moeny = 2, //��Ǯ
TDropType_Cnt
};

struct SDropGroupItem:public TemplateBase
{
	SDropGroupItem()
	{
		rate = 0;
	num = 0;
	}
	//��������
	TDropType dropType;
	//����:0~1��С��
	float rate;
	//������ֵ
	int32t num;

//method impl 
	bool ReadJsonImpl(const CSJson::Value& obj)
	{
				//��������
	 getJsonVal(obj["dropType"], (int&)dropType); 
		//����:0~1��С��
	 getJsonVal(obj["rate"], rate); 
		//������ֵ
	 getJsonVal(obj["num"], num); 
		return true;
	}
};

class TemplateArms : public TemplateBase
{
public:
	TemplateArms();
	~TemplateArms(){}
	
	bool ReadJsonImpl(const CSJson::Value& obj);
	int32t getSNImpl() {return m_sn;}
	
public:
	const std::string& getShowname() const{ return m_ShowName;}
	const std::string& getAnimatepath() const{ return m_AnimatePath;}
	TAimMoveType getMovetype() const{ return m_MoveType;}
	int32t getAttack() const{ return m_Attack;}
	int32t getDefence() const{ return m_Defence;}
	int32t getHp() const{ return m_HP;}
	int32t getCd() const{ return m_CD;}
	int32t getSpeed() const{ return m_Speed;}
	TArmType getArmtype() const{ return m_ArmType;}
	TCostType getCosttype() const{ return m_CostType;}
	int32t getCostnum() const{ return m_CostNum;}
	int32t getAiconfig() const{ return m_AIConfig;}
	const vector<int32t>& getActiveskill() const{ return m_ActiveSkill;}
	const vector<int32t>& getPassiveskill() const{ return m_PassiveSkill;}
	int32t getBossskill() const{ return m_BossSkill;}
	const vector<SDropGroupItem>& getDropgroup() const{ return m_DropGroup;}

	
private:
	//sn
	int32t m_sn;
	//��Ϸ����ʾ��UI���ٻ���Ӧ���ֵ������
	std::string m_ShowName;
	//��Ӧ�Ķ���Ŀ¼�� ֻ���ļ���������
	std::string m_AnimatePath;
	//�������ͣ� ������߷���
	TAimMoveType m_MoveType;
	//INT�����ֵ���������
	int32t m_Attack;
	//INT�����ֵ���������
	int32t m_Defence;
	//INT�����ֵ���������
	int32t m_HP;
	//cd
	int32t m_CD;
	//�ٶȣ����أ�INT
	int32t m_Speed;
	//���ֵ����ͣ�½�صĻ��߿��е�
	TArmType m_ArmType;
	//��Դ��ɱ��
	TCostType m_CostType;
	//INT����Ӧ�������Դ������Ч
	int32t m_CostNum;
	//INT����Ӧ�������Դ������Ч
	int32t m_AIConfig;
	//ѡ�뼼��ģ�壬������ID
	vector<int32t> m_ActiveSkill;
	//ѡ�뼼��ģ�壬������ID
	vector<int32t> m_PassiveSkill;
	//ѡ�뼼��ģ�壬������ID
	int32t m_BossSkill;
	//�������
	vector<SDropGroupItem> m_DropGroup;

};

#endif //_TEMPLATEARMS_H__
