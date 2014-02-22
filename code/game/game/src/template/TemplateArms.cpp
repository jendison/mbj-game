//auto create by tocpp.rb, plz don't modify it!
//2013-10-29 17:16:20 +0800

#include "TemplateArms.h"

using std::string;

TemplateArms::TemplateArms()
{
	m_sn = 0;
	m_Attack = 0;
	m_Defence = 0;
	m_HP = 0;
	m_CD = 0;
	m_Speed = 0;
	m_CostType =(TCostType) 1;
	m_CostNum = 0;
	m_AIConfig = 0;
//
}

bool TemplateArms::ReadJsonImpl(const CSJson::Value& obj)
{
		//sn
	 getJsonVal(obj["sn"], m_sn); 
		//��Ϸ����ʾ��UI���ٻ���Ӧ���ֵ������
	 getJsonVal(obj["ShowName"], m_ShowName); 
		//��Ӧ�Ķ���Ŀ¼�� ֻ���ļ���������
	 getJsonVal(obj["AnimatePath"], m_AnimatePath); 
		//�������ͣ� ������߷���
	 getJsonVal(obj["MoveType"], (int&)m_MoveType); 
		//INT�����ֵ���������
	 getJsonVal(obj["Attack"], m_Attack); 
		//INT�����ֵ���������
	 getJsonVal(obj["Defence"], m_Defence); 
		//INT�����ֵ���������
	 getJsonVal(obj["HP"], m_HP); 
		//cd
	 getJsonVal(obj["CD"], m_CD); 
		//�ٶȣ����أ�INT
	 getJsonVal(obj["Speed"], m_Speed); 
		//���ֵ����ͣ�½�صĻ��߿��е�
	 getJsonVal(obj["ArmType"], (int&)m_ArmType); 
		//��Դ��ɱ��
	 getJsonVal(obj["CostType"], (int&)m_CostType); 
		//INT����Ӧ�������Դ������Ч
	 getJsonVal(obj["CostNum"], m_CostNum); 
		//INT����Ӧ�������Դ������Ч
	 getJsonVal(obj["AIConfig"], m_AIConfig); 
		//ѡ�뼼��ģ�壬������ID
	 getJsonVal(obj["ActiveSkill"], m_ActiveSkill); 
		//ѡ�뼼��ģ�壬������ID
	 getJsonVal(obj["PassiveSkill"], m_PassiveSkill); 
		//ѡ�뼼��ģ�壬������ID
	 getJsonVal(obj["BossSkill"], m_BossSkill); 

				//�������
	
		 const CSJson::Value& tmp = obj["DropGroup"];
		uint32t nSize = tmp.size();
		for (uint32t i = 0; i < nSize; ++i)
		{
			SDropGroupItem n;
			n.ReadJsonImpl(tmp[i]);
			m_DropGroup.push_back(n);
		}		
		
	return true;
}



