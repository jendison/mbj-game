//auto create by tocpp.rb, plz don't modify it!
//2013-10-29 17:14:25 +0800

#include "TemplateSkill.h"

using std::string;

TemplateSkill::TemplateSkill()
{
	m_sn = 0;
	m_Distance = 0;
	m_SkillCD = 0;
	m_TrajectorySpeed = 0;
	m_scriptFunc = "20";
////////
}

bool TemplateSkill::ReadJsonImpl(const CSJson::Value& obj)
{
		//sn
	 getJsonVal(obj["sn"], m_sn); 
		//��ʾ��
	 getJsonVal(obj["ShowName"], m_ShowName); 
		//ʩ������
	 getJsonVal(obj["Distance"], m_Distance); 
		//�Ƿ��Զ�����
	 getJsonVal(obj["IsAutoPlay"], (int&)m_IsAutoPlay); 
		//����CD
	 getJsonVal(obj["SkillCD"], m_SkillCD); 
		//������Ч���ƶ��ٶ�
	 getJsonVal(obj["TrajectorySpeed"], m_TrajectorySpeed); 
		//����˺��Ľű�����
	 getJsonVal(obj["scriptFunc"], m_scriptFunc); 
		//���������趨
	 m_UpLevelSetting.ReadJsonImpl(obj["UpLevelSetting"]); 
		//AOE�ж���Χ����
	 getJsonVal(obj["AOEType"], (int&)m_AOEType); 
		//���ʱ�������ʼ���ŵ�������AOE��Ч
	 getJsonVal(obj["StartPlaySkillEffectTime"], m_StartPlaySkillEffectTime); 
		//AOE�ж���Χ����-ֱ��
	 m_LineSetting.ReadJsonImpl(obj["LineSetting"]); 
		//AOE�ж���Χ�������Σ������ﳯ����ʱ��Ϊ�����򣬷�ΧΪ[-180,180]
	 m_SectorSetting.ReadJsonImpl(obj["SectorSetting"]); 

				//��Ч��Դ
	
		 const CSJson::Value& tmp = obj["effectRes"];
		uint32t nSize = tmp.size();
		for (uint32t i = 0; i < nSize; ++i)
		{
			SkillEffect n;
			n.ReadJsonImpl(tmp[i]);
			m_effectRes.push_back(n);
		}		
		
	return true;
}



